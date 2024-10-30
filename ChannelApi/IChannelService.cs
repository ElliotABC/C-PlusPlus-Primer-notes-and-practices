namespace ChannelApi;

public interface IChannelService
{
    Task WriteMessage(string message);
    Task ReadMessage();
    Task ProcessMessage(CancellationToken cancellationToken);
}