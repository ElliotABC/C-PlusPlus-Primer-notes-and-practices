using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

public enum LoaderError
{
    ProcessListSnapshot,
    ModuleHandle,
    FunctionAddress,
    OpenProcessNull,
    AllocationFailed
}

public class Loader
{
    public static string ErrorToString(LoaderError err)
    {
        switch (err)
        {
            case LoaderError.ProcessListSnapshot: return "Couldn't create a process list snapshot.";
            case LoaderError.ModuleHandle: return "Couldn't find a module handle.";
            case LoaderError.FunctionAddress: return "Couldn't find a function address.";
            case LoaderError.OpenProcessNull: return "OpenProcess returned 0, make sure Process is opened before running this.";
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
        IntPtr proc = OpenProcess(ProcessAccessFlags.CreateThread | ProcessAccessFlags.VirtualMemoryOperation | ProcessAccessFlags.VirtualMemoryWrite, false, processId);
        if (proc == IntPtr.Zero)
        {
            Console.Error.WriteLine(ErrorToString(LoaderError.OpenProcessNull));
            return false;
        }

        int pathLen = dllPath.Length + 1;
        IntPtr allocation = VirtualAllocEx(proc, IntPtr.Zero, pathLen, AllocationType.Commit | AllocationType.Reserve, MemoryProtection.ReadWrite);
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

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr OpenProcess(ProcessAccessFlags dwDesiredAccess, [MarshalAs(UnmanagedType.Bool)] bool bInheritHandle, int dwProcessId);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, int dwSize, AllocationType flAllocationType, MemoryProtection flProtect);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, string lpBuffer, int nSize, out int lpNumberOfBytesWritten);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, int dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, int dwCreationFlags, out uint lpThreadId);

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

    public enum FreeType : uint
    {
        Release = 0x8000
    }
}

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Waiting for Process to start");

        int processId = 0;
        while (processId == 0)
        {
            foreach (var processName in new[] { "notepad", "notepad", "notepad" })
            {
                processId = Loader.GetProcessIdByName(processName);
                if (processId != 0)
                {
                    break;
                }
            }
        }

        Console.WriteLine($"Injecting into {processId}");

        string exePath = Process.GetCurrentProcess().MainModule.FileName;
        string dllPath = Path.Combine(Path.GetDirectoryName(exePath), "Library.dll");

        Console.WriteLine($"Library path: {dllPath}");

        if (!Loader.Inject(processId, dllPath))
        {
            Console.Error.WriteLine("Failed to inject the library.");
            return;
        }

        Console.WriteLine("Done.");
    }
}