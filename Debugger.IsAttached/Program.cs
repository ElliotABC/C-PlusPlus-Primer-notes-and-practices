using System.Diagnostics;
// 不能判断外部调试器附加
while (true)
{
    if (Debugger.IsAttached)
    {
        Console.WriteLine("Debugger is attached.");
    }
    else
    {
        Console.WriteLine("Debugger is not attached.");
    }
}