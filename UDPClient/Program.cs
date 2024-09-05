using System.Net;
using System.Net.Sockets;
using System.Text;

namespace UDPClient;

class UdpClientDemo
{
    static void Main(string[] args)
    {
        const int port = 12345;
        const string serverIp = "127.0.0.1"; // 服务器 IP 地址

        // 创建一个 UDP Socket
        using (UdpClient client = new UdpClient())
        {
            IPEndPoint serverEP = new IPEndPoint(IPAddress.Parse(serverIp), port);

            Console.WriteLine("Sending message to server...");

            // 发送消息
            string message = "Hello from client!";
            byte[] messageBytes = Encoding.UTF8.GetBytes(message);
            client.Send(messageBytes, messageBytes.Length, serverEP);

            // 接收回复
            byte[] receivedBytes = client.Receive(ref serverEP);
            string receivedData = Encoding.UTF8.GetString(receivedBytes);

            Console.WriteLine("Received response from {0}:{1} - {2}", serverEP.Address, serverEP.Port, receivedData);
        }
    }
}