using System.Diagnostics;
using System.Runtime.InteropServices;
using Newtonsoft.Json;

Console.WriteLine("Waiting for Process to start");
string exePath = Process.GetCurrentProcess().MainModule.FileName;
string dllPath = Path.Combine(Path.GetDirectoryName(exePath), "Library.dll");
string jsonPath = Path.Combine(Path.GetDirectoryName(exePath), "loader.json");
if (!File.Exists(jsonPath))
{
    ExeData exeData = new ExeData { Names = new List<string> { "MyApp" } };
    string jsonData = JsonConvert.SerializeObject(exeData, Formatting.Indented);
    File.WriteAllText(jsonPath, jsonData);
    Console.WriteLine("loader.json created and populated with data.");
    Console.ForegroundColor = ConsoleColor.Red;
    Console.WriteLine("Please run the loader again.");
    return;
}

var processData = JsonConvert.DeserializeObject<ExeData>(File.ReadAllText(jsonPath));
int processId = 0;
while (processId == 0)
{
    foreach (var processName in processData.Names)
    {
        processId = Loader.GetProcessIdByName(processName);
        if (processId != 0)
        {
            break;
        }
    }
}

Console.WriteLine($"Injecting into {processId}");

Console.WriteLine($"Library path: {dllPath}");

if (!Loader.Inject_APC("notepad", dllPath))
{
    Console.Error.WriteLine("Failed to inject the library.");
    return;
}
// if (!Loader.Inject(processId, dllPath))
// {
//     Console.Error.WriteLine("Failed to inject the library.");
//     return;
// }
// int pid;
// List<int> tids = new List<int>(); // 需要获取进程所有的线程ID
// Loader.FindProcess2("Code", out pid, tids);
Console.WriteLine("Done.");

enum LoaderError
{
    ProcessListSnapshot,
    ModuleHandle,
    FunctionAddress,
    OpenProcessNull,
    AllocationFailed
}

class Loader
{
    public static bool FindProcess2(string processName, out int dwProcess, List<int> dwThreads)
    {
        dwProcess = 0;
        dwThreads.Clear();

        Process[] processes = Process.GetProcesses();
        foreach (var process in processes)
        {
            if (process.ProcessName.Equals(processName, StringComparison.OrdinalIgnoreCase))
            {
                foreach (ProcessThread thread in process.Threads)
                {
                    dwThreads.Add(thread.Id);
                }
                dwProcess = process.Id;
                return true;
            }
            
        }
        return false;
    }
    public static string ErrorToString(LoaderError err)
    {
        switch (err)
        {
            case LoaderError.ProcessListSnapshot: return "Couldn't create a process list snapshot.";
            case LoaderError.ModuleHandle: return "Couldn't find a module handle.";
            case LoaderError.FunctionAddress: return "Couldn't find a function address.";
            case LoaderError.OpenProcessNull:
                return "OpenProcess returned 0, make sure Process is opened before running this.";
            case LoaderError.AllocationFailed: return "Couldn't allocate memory for the DLL path.";
            default: return "Unknown error.";
        }
    }

    public static int GetProcessIdByName(string name)
    {
        Process[] processes = Process.GetProcesses();
        foreach (var process in processes)
        {
            if (process.ProcessName.Equals(name, StringComparison.OrdinalIgnoreCase))
            {
                return process.Id;
            }
        }

        return 0;
    }

    public static IntPtr GetFunctionAddress(string module, string function)
    {
        IntPtr handle = GetModuleHandle(module);
        if (handle == IntPtr.Zero)
        {
            Console.Error.WriteLine(ErrorToString(LoaderError.ModuleHandle));
            return IntPtr.Zero;
        }

        IntPtr func = GetProcAddress(handle, function);
        if (func == IntPtr.Zero)
        {
            Console.Error.WriteLine(ErrorToString(LoaderError.FunctionAddress));
            return IntPtr.Zero;
        }

        return func;
    }

    public static bool Inject(int processId, string dllPath)
    {
        IntPtr proc =
            OpenProcess(
                ProcessAccessFlags.CreateThread | ProcessAccessFlags.VirtualMemoryOperation |
                ProcessAccessFlags.VirtualMemoryWrite, false, processId);
        if (proc == IntPtr.Zero)
        {
            Console.Error.WriteLine(ErrorToString(LoaderError.OpenProcessNull));
            return false;
        }

        int pathLen = dllPath.Length + 1;
        IntPtr allocation = VirtualAllocEx(proc, IntPtr.Zero, pathLen, AllocationType.Commit | AllocationType.Reserve,
            MemoryProtection.ReadWrite);
        if (allocation == IntPtr.Zero)
        {
            Console.Error.WriteLine(ErrorToString(LoaderError.AllocationFailed));
            CloseHandle(proc);
            return false;
        }

        Console.WriteLine($"Allocated memory for the library path at {allocation.ToString("X")}");

        if (!WriteProcessMemory(proc, allocation, dllPath, pathLen, out _))
        {
            Console.Error.WriteLine("WriteProcessMemory failed.");
            VirtualFreeEx(proc, allocation, 0, FreeType.Release);
            CloseHandle(proc);
            return false;
        }

        IntPtr loadLibrary = GetFunctionAddress("kernel32.dll", "LoadLibraryA");
        if (loadLibrary == IntPtr.Zero)
        {
            VirtualFreeEx(proc, allocation, 0, FreeType.Release);
            CloseHandle(proc);
            return false;
        }

        Console.WriteLine($"LoadLibraryA found at {loadLibrary.ToString("X")}");

        IntPtr thread = CreateRemoteThread(proc, IntPtr.Zero, 0, loadLibrary, allocation, 0, out _);
        if (thread == IntPtr.Zero)
        {
            Console.Error.WriteLine("CreateRemoteThread failed.");
            VirtualFreeEx(proc, allocation, 0, FreeType.Release);
            CloseHandle(proc);
            return false;
        }

        WaitForSingleObject(thread, Timeout.Infinite);
        CloseHandle(thread);
        VirtualFreeEx(proc, allocation, 0, FreeType.Release);
        CloseHandle(proc);
        return true;
    }

    public static bool Inject_APC(string processName, string dllPath)
    {
        int pid;
        List<int> tids = new List<int>(); // 需要获取进程所有的线程ID
        if (FindProcess2(processName, out pid, tids))
        {
            IntPtr proc =
                OpenProcess(
                    ProcessAccessFlags.CreateThread | ProcessAccessFlags.VirtualMemoryOperation |
                    ProcessAccessFlags.VirtualMemoryWrite, false, pid);
            if (proc == IntPtr.Zero)
            {
                Console.Error.WriteLine(ErrorToString(LoaderError.OpenProcessNull));
                return false;
            }

            int pathLen = dllPath.Length + 1;
            IntPtr allocation = VirtualAllocEx(proc, IntPtr.Zero, pathLen,
                AllocationType.Commit | AllocationType.Reserve,
                MemoryProtection.ReadWrite);
            if (allocation == IntPtr.Zero)
            {
                Console.Error.WriteLine(ErrorToString(LoaderError.AllocationFailed));
                CloseHandle(proc);
                return false;
            }

            Console.WriteLine($"Allocated memory for the library path at {allocation.ToString("X")}");

            if (!WriteProcessMemory(proc, allocation, dllPath, pathLen, out _))
            {
                Console.Error.WriteLine("WriteProcessMemory failed.");
                VirtualFreeEx(proc, allocation, 0, FreeType.Release);
                CloseHandle(proc);
                return false;
            }

            foreach (var thread in tids)
            {
                IntPtr hThread = OpenThread(DesiredAccess.ThreadSetContext, false, thread);
                if (hThread == IntPtr.Zero)
                {
                    Console.WriteLine("OpenThread failed");
                    return false;
                }

                IntPtr loadLibraryW = GetProcAddress(GetModuleHandle("kernel32"), "LoadLibraryW");
                QueueUserAPC(loadLibraryW, hThread, allocation); // 将APC注入到目标进程中
            }

            VirtualFreeEx(proc, allocation, 0, FreeType.Release);
            CloseHandle(proc);
        }

        return true;
    }

    
    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern IntPtr CreateToolhelp32Snapshot(uint dwFlags, uint th32ProcessID);

    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern bool Process32First(IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern bool Process32Next(IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern bool Thread32First(IntPtr hSnapshot, ref THREADENTRY32 lpte);

    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern bool Thread32Next(IntPtr hSnapshot, ref THREADENTRY32 lpte);
    
    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern IntPtr OpenThread(DesiredAccess dwDesiredAccess, bool bInheritHandle, int dwThreadId);

    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern bool QueueUserAPC(IntPtr pfnAPC, IntPtr hThread, IntPtr dwData);
    
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr OpenProcess(ProcessAccessFlags dwDesiredAccess,
        [MarshalAs(UnmanagedType.Bool)] bool bInheritHandle, int dwProcessId);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, int dwSize,
        AllocationType flAllocationType, MemoryProtection flProtect);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, string lpBuffer, int nSize,
        out int lpNumberOfBytesWritten);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, int dwStackSize,
        IntPtr lpStartAddress, IntPtr lpParameter, int dwCreationFlags, out uint lpThreadId);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr GetModuleHandle(string lpModuleName);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool VirtualFreeEx(IntPtr hProcess, IntPtr lpAddress, int dwSize, FreeType dwFreeType);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool CloseHandle(IntPtr hObject);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool WaitForSingleObject(IntPtr hHandle, int dwMilliseconds);

    [Flags]
    public enum ProcessAccessFlags : uint
    {
        CreateThread = 0x0002,
        VirtualMemoryOperation = 0x0008,
        VirtualMemoryWrite = 0x0020
    }

    [Flags]
    public enum AllocationType : uint
    {
        Commit = 0x1000,
        Reserve = 0x2000
    }

    [Flags]
    public enum MemoryProtection : uint
    {
        ReadWrite = 0x04
    }

    [Flags]
    public enum FreeType : uint
    {
        Release = 0x8000,
        Decommit = 0x4000
    }
    
    [Flags]
    public enum DesiredAccess : uint
    {
        ThreadSetContext = 0x0010
    }
    
    private const uint TH32CS_SNAPPROCESS = 0x00000002;
    private const uint TH32CS_SNAPTHREAD = 0x00000004;
    private const uint INVALID_HANDLE_VALUE = 0xFFFFFFFF;

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
    private struct PROCESSENTRY32
    {
        public uint dwSize;
        public uint cntUsage;
        public uint th32ProcessID;
        public IntPtr th32DefaultHeapID;
        public uint th32ModuleID;
        public uint cntThreads;
        public uint th32ParentProcessID;
        public int pcPriClassBase;
        public uint dwFlags;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
        public string szExeFile;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
    private struct THREADENTRY32
    {
        public uint dwSize;
        public uint cntUsage;
        public uint th32ThreadID;
        public IntPtr th32OwnerProcessID;
        public int tpBasePri;
        public int tpDeltaPri;
        public uint dwFlags;
    }

}

class ExeData
{
    public List<string> Names;
}