using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;

class Program
{
    [DllImport("kernel32.dll", SetLastError = true)]
    static extern IntPtr CreateToolhelp32Snapshot(uint dwFlags, uint th32ProcessID);

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool Process32First(IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool Process32Next(IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool CloseHandle(IntPtr hObject);

    [DllImport("kernel32.dll", SetLastError = true)]
    static extern IntPtr OpenProcess(uint processAccess, bool bInheritHandle, int processId);

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool CheckRemoteDebuggerPresent(IntPtr hProcess, ref bool isDebuggerPresent);

    [DllImport("advapi32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool OpenProcessToken(IntPtr ProcessHandle, uint DesiredAccess, out IntPtr TokenHandle);

    [DllImport("advapi32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool LookupPrivilegeValue(string lpSystemName, string lpName, out LUID lpLuid);

    [DllImport("advapi32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool AdjustTokenPrivileges(IntPtr TokenHandle, bool DisableAllPrivileges, ref TOKEN_PRIVILEGES NewState, uint BufferLength, IntPtr PreviousState, IntPtr ReturnLength);

    [StructLayout(LayoutKind.Sequential)]
    struct PROCESSENTRY32
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

    [StructLayout(LayoutKind.Sequential)]
    struct LUID
    {
        public uint LowPart;
        public int HighPart;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct TOKEN_PRIVILEGES
    {
        public uint PrivilegeCount;
        public LUID Luid;
        public uint Attributes;
    }

    const uint TH32CS_SNAPPROCESS = 0x00000002;
    const uint PROCESS_ALL_ACCESS = 0x001F0FFF;
    const uint TOKEN_ADJUST_PRIVILEGES = 0x0020;
    const uint SE_PRIVILEGE_ENABLED = 0x00000002;

    static void Main()
    {
        SetPrivileges();
        ProcessT processT = new ProcessT();
        Console.WriteLine("Enter Process Name: ");
        processT.ProcessName = Console.ReadLine();

        if (processT.IsDbgPresent())
        {
            Console.WriteLine("Debugger is attached");
        }
    }

    static void SetPrivileges()
    {
        IntPtr hToken;
        TOKEN_PRIVILEGES tokenPriv;

        IntPtr hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, Process.GetCurrentProcess().Id);
        tokenPriv.PrivilegeCount = 1;
        LookupPrivilegeValue(null, "SeDebugPrivilege", out tokenPriv.Luid);
        tokenPriv.Attributes = SE_PRIVILEGE_ENABLED;
        OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, out hToken);
        AdjustTokenPrivileges(hToken, false, ref tokenPriv, 0, IntPtr.Zero, IntPtr.Zero);

        CloseHandle(hToken);
        CloseHandle(hProcess);
    }

    class ProcessT
    {
        public string ProcessName { get; set; }

        public bool IsDbgPresent()
        {
            int pid = FindProcessID(ProcessName);
            if (pid == -1)
                return false;

            IntPtr processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
            bool isDebuggerPresent = false;
            CheckRemoteDebuggerPresent(processHandle, ref isDebuggerPresent);
            CloseHandle(processHandle);
            return isDebuggerPresent;
        }

        private int FindProcessID(string processName)
        {
            IntPtr hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            if (hSnapshot == IntPtr.Zero)
                return -1;

            PROCESSENTRY32 processEntry = new PROCESSENTRY32();
            processEntry.dwSize = (uint)Marshal.SizeOf(typeof(PROCESSENTRY32));

            if (!Process32First(hSnapshot, ref processEntry))
            {
                CloseHandle(hSnapshot);
                return -1;
            }

            do
            {
                if (string.Equals(processEntry.szExeFile, processName, StringComparison.OrdinalIgnoreCase))
                {
                    CloseHandle(hSnapshot);
                    return (int)processEntry.th32ProcessID;
                }
            } while (Process32Next(hSnapshot, ref processEntry));

            CloseHandle(hSnapshot);
            return -1;
        }
    }
}