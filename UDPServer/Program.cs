using System.Net;
using System.Net.Sockets;
using System.Text;

namespace UDPServer;

class UdpServer
{
    static void Main(string[] args)
    {
        const int port = 12345;
        const string listenIp = "127.0.0.1"; // 监听本地 IP 地址

        // 创建一个 UDP Socket
        using (UdpClient server = new UdpClient(port))
        {
            IPEndPoint remoteEP = new IPEndPoint(IPAddress.Any, 0);

            Console.WriteLine("UDP Server is listening on port {0}", port);

            while (true)
            {
                // 接收数据
                byte[] receivedBytes = server.Receive(ref remoteEP);
                string receivedData = Encoding.UTF8.GetString(receivedBytes);

                Console.WriteLine("Received message from {0}:{1} - {2}", remoteEP.Address, remoteEP.Port, receivedData);

                // 回复消息
                string response = "Hello from server!";
                byte[] responseBytes = Encoding.UTF8.GetBytes(response);
                server.Send(responseBytes, responseBytes.Length, remoteEP);
            }
        }
    }
}