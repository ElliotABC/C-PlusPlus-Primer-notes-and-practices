using System;
using System.Threading;
using System.Threading.Tasks;

class Program
{
    static async Task Main(string[] args)
    {
        Console.WriteLine("Starting...");

        using (var cts = new CancellationTokenSource())
        {
            var cancellationToken = cts.Token;
            var task = DoSomethingAsync(cancellationToken);

            // 模拟取消
            await Task.Delay(1000);
            cts.Cancel();

            try
            {
                await task;
            }
            catch (OperationCanceledException)
            {
                Console.WriteLine("Task was canceled.");
            }
        }

        Console.WriteLine("Finished!");
    }

    static async Task DoSomethingAsync(CancellationToken cancellationToken)
    {
        Console.WriteLine("Doing something...");
        while (!cancellationToken.IsCancellationRequested)
        {
            await Task.Delay(500, cancellationToken);
            Console.WriteLine("Still working...");
        }
    }
}