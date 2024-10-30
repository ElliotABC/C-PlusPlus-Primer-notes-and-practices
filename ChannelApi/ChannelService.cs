using System.Threading.Channels;

namespace ChannelApi;

public class ChannelService : IChannelService
{
    private readonly ChannelWriter<string> _channelWriter;
    private  readonly ChannelReader<string> _channelReader;
    public ChannelService(ChannelWriter<string> channelWriter, ChannelReader<string> channelReader)
    {
        _channelWriter = channelWriter;
        _channelReader = channelReader;
    }
    
    public async Task WriteMessage(string message)
    {
        await _channelWriter.WriteAsync(message);
    }

    public async Task ReadMessage()
    {
        await _channelReader.ReadAsync();
    }

    public async Task ProcessMessage(CancellationToken cancellationToken)
    {
        while (await _channelReader.WaitToReadAsync(cancellationToken))
        {
            if (cancellationToken.IsCancellationRequested)
                return;

            while (_channelReader.TryRead(out var message))
            {
                // 处理消息
                Console.WriteLine($"Received message: {message}");
                await Task.Delay(1000);
            }
        }
    }
}