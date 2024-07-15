using System.Diagnostics;
using System.Runtime.InteropServices;

[DllImport("kernel32.dll", SetLastError = true)]
static extern bool CheckRemoteDebuggerPresent(IntPtr hProcess, ref bool isDebuggerPresent);

bool isDebuggerPresent = false;
IntPtr hProcess = Process.GetCurrentProcess().Handle;

while (true)
{
    CheckRemoteDebuggerPresent(hProcess, ref isDebuggerPresent);

    if (isDebuggerPresent)
    {
        Console.WriteLine("Debugger is attached.");
    }
    else
    {
        Console.WriteLine("Debugger is not attached.");
    }
}