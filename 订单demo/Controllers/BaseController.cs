using Microsoft.AspNetCore.Mvc;
using 订单demo.Models;

namespace 订单demo.Controllers;

[Route("api/[controller]/[action]")]
[ApiController]
public class BaseController : Controller
{
    protected ApiResult Success(string messge = "")
    {
        return new ApiResult { Message = messge, Data = new object() };
    }

    protected ApiResult Success(object data)
    {
        return new ApiResult { Data = data };
    }

    protected ApiResult Fail(string errorCode, string errorMessage)
    {
        return new ApiResult
        {
            Success = false,
            ErrorCode = errorCode,
            Message = errorMessage
        };
    }
}