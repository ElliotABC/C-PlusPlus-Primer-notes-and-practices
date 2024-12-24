using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
// ReSharper disable InconsistentNaming

const uint PROCESS_CREATE_THREAD = 0x0002;
const uint PROCESS_QUERY_INFORMATION = 0x0400;
const uint PROCESS_VM_OPERATION = 0x0008;
const uint PROCESS_VM_WRITE = 0x0020;
const uint PROCESS_VM_READ = 0x0010;

const uint MEM_COMMIT = 0x00001000;
const uint MEM_RESERVE = 0x00002000;
const uint PAGE_READWRITE = 4;

if (args.Length != 2)
{
    Console.WriteLine("[HELP] inject.exe <dll> <process>");
    return;
}

string dllName = args[0];
string processName = args[1];

int processId = GetProcessByName(processName);
if (processId == -1)
{
    Console.WriteLine("An error occurred when trying to find the target process.");
    return;
}

Console.WriteLine("[DLL Injector]");
Console.WriteLine("Process : {0}", processName);
Console.WriteLine("Process ID : {0}\n", processId);

string fullDllPath = Path.GetFullPath(dllName);
if (string.IsNullOrEmpty(fullDllPath))
{
    Console.WriteLine("An error occurred when trying to get the full path of the DLL.");
    return;
}

IntPtr hTargetProcess =
    OpenProcess(
        PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ,
        false, processId);
if (hTargetProcess == IntPtr.Zero)
{
    Console.WriteLine("An error occurred when trying to open the target process.");
    return;
}

Console.WriteLine("[PROCESS INJECTION]");
Console.WriteLine("Process opened successfully.");

IntPtr lpPathAddress = VirtualAllocEx(hTargetProcess, IntPtr.Zero,
    (uint)((fullDllPath.Length + 1) * Marshal.SizeOf(typeof(char))), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
if (lpPathAddress == IntPtr.Zero)
{
    Console.WriteLine("An error occurred when trying to allocate memory in the target process.");
    return;
}

Console.WriteLine("Memory allocated at 0x{0:X}", (int)lpPathAddress);

byte[] dllBytes = Encoding.ASCII.GetBytes(fullDllPath);
IntPtr bytesWritten;
if (!WriteProcessMemory(hTargetProcess, lpPathAddress, dllBytes, (uint)dllBytes.Length, out bytesWritten))
{
    Console.WriteLine("An error occurred when trying to write the DLL path in the target process.");
    return;
}

Console.WriteLine("DLL path written successfully.");

IntPtr hModule = GetModuleHandle("kernel32.dll");
if (hModule == IntPtr.Zero)
{
    Console.WriteLine("An error occurred when trying to get the module handle for kernel32.dll.");
    return;
}

IntPtr lpFunctionAddress = GetProcAddress(hModule, "LoadLibraryA");
if (lpFunctionAddress == IntPtr.Zero)
{
    Console.WriteLine("An error occurred when trying to get the address of LoadLibraryA.");
    return;
}

Console.WriteLine("LoadLibraryA address at 0x{0:X}", (int)lpFunctionAddress);

IntPtr hThreadCreationResult =
    CreateRemoteThread(hTargetProcess, IntPtr.Zero, 0, lpFunctionAddress, lpPathAddress, 0, IntPtr.Zero);
if (hThreadCreationResult == IntPtr.Zero)
{
    Console.WriteLine("An error occurred when trying to create the thread in the target process.");
    return;
}

Console.WriteLine("DLL Injected!");

CloseHandle(hThreadCreationResult);
CloseHandle(hTargetProcess);


static int GetProcessByName(string processName)
{
    Process[] processes = Process.GetProcessesByName(Path.GetFileNameWithoutExtension(processName));
    foreach (Process process in processes)
    {
        if (process.ProcessName.Equals(processName, StringComparison.OrdinalIgnoreCase))
        {
            return process.Id;
        }
    }

    return -1;
}

[DllImport("kernel32.dll", SetLastError = true)]
static extern IntPtr OpenProcess(uint processAccess, bool bInheritHandle, int processId);

[DllImport("kernel32.dll", SetLastError = true)]
static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType,
    uint flProtect);

[DllImport("kernel32.dll", SetLastError = true)]
static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize,
    out IntPtr lpNumberOfBytesWritten);

[DllImport("kernel32.dll", SetLastError = true)]
static extern IntPtr GetModuleHandle(string lpModuleName);

[DllImport("kernel32.dll", SetLastError = true)]
static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

[DllImport("kernel32.dll", SetLastError = true)]
static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize,
    IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

[DllImport("kernel32.dll", SetLastError = true)]
static extern bool CloseHandle(IntPtr hObject);

