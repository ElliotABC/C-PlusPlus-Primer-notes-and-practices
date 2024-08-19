using System.Net;
using System.Net.Http.Json;
using System.Net.Sockets;
using Polly;

namespace PollyTTT;

public abstract class Program
{
    public static async Task Main()
    {
        var retry = Policy.Handle<SocketException>()
            .Or<HttpRequestException>()
            .RetryAsync(3, (exception, retryCount) =>
            {
                Console.WriteLine($"重试次数: {retryCount}");
            });

        // 熔断策略
        var circuitBreaker = Policy.Handle<SocketException>()
            .Or<HttpRequestException>()
            .CircuitBreakerAsync(5, TimeSpan.FromSeconds(30), onBreak: (exception, duration) =>
            {
                Console.WriteLine($"熔断器打开，将在 {duration.TotalSeconds} 秒后尝试半开状态");
            }, onReset: () =>
            {
                Console.WriteLine("熔断器重置为关闭状态");
            }, onHalfOpen: () =>
            {
                Console.WriteLine("熔断器进入半开状态");
            });

        // 结合重试和熔断策略
        var combinedPolicy = retry.WrapAsync(circuitBreaker);

        await combinedPolicy.ExecuteAsync(HttpClientTest);

        await retry.ExecuteAsync(HttpClientTest);
    }

    private static async Task<HttpResponseMessage> HttpClientTest()
    {
        using (var client = new HttpClient())
        {
            var data = new
            {
                hospitalIds = "",
                isActivate = true,
                parentId = 0,
                pwd = "qaz123Qwe",
                roleId = 2,
                roleName = "",
            };

            HttpResponseMessage response = await client.PostAsJsonAsync("http://localhost:44372/api/CustomUser/AddCustomUser", data);

            if (response.IsSuccessStatusCode)
            {
                string result = await response.Content.ReadAsStringAsync();
                Console.WriteLine(result);
            }
            else
            {
                Console.WriteLine($"请求失败: {response.StatusCode}");
            }

            return response;
        }
    }
}