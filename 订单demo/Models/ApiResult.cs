namespace 订单demo.Models;

public class ApiResult
{
    public bool Success { get; set; } = true;

    public string ErrorCode { get; set; }

    public string Message { get; set; }

    public object Data { get; set; }
}