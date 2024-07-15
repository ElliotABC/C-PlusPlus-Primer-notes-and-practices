using System.Runtime.InteropServices;

[DllImport("kernel32.dll")]
static extern bool IsDebuggerPresent();

while (true)
{
    if (IsDebuggerPresent())
    {
        Console.WriteLine("Debugger is attached.");
    }
    else
    {
        Console.WriteLine("Debugger is not attached.");
    }
    Thread.Sleep(1000);
}