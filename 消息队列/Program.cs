using System.Threading.Channels;

class Program
{
    static async Task Main(string[] args)
    {
        // 创建一个容量为0的无界通道
        var channel = Channel.CreateUnbounded<string>();

        // 启动消费者任务
        var consumerTask = ConsumeMessagesAsync(channel);

        // 发送一些消息
        for (int i = 0; i < 10; i++)
        {
            channel.Writer.TryWrite($"Message {i}");
            await Task.Delay(1000); // 模拟消息发送延迟
        }

        // 完成消息发送
        channel.Writer.Complete();

        // 等待消费者任务完成
        await consumerTask;
    }

    static async Task ConsumeMessagesAsync(ChannelReader<string> reader)
    {
        while (await reader.WaitToReadAsync())
        {
            while (reader.TryRead(out var message))
            {
                Console.WriteLine($"Received: {message}");
            }
        }
    }
}