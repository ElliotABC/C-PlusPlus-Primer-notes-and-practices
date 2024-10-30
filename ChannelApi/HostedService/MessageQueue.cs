using System.Threading.Channels;

namespace ChannelApi.HostedService;

public class MessageQueue : BackgroundService
{
    private readonly IServiceProvider _services;

    public MessageQueue(IServiceProvider services)
    {
        _services = services;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        using var scope = _services.CreateScope();
        var writerService = scope.ServiceProvider.GetRequiredService<IChannelService>();
        await writerService.ProcessMessage(stoppingToken);
    }

    // private async Task ProcessMessageAsync()
    // {
    //     while (await _reader.WaitToReadAsync())
    //     {
    //         var message = await _reader.ReadAsync();
    //         Console.WriteLine($"Message received: {message}");
    //     }
    // }
}