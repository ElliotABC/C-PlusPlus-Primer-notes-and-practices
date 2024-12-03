using Microsoft.AspNetCore.Mvc;
using 订单demo.Dto;
using 订单demo.Service;

namespace 订单demo.Controllers;

public class OrderController : BaseController
{
    private readonly IOrderService _orderService;

    public OrderController(IOrderService orderService)
    {
        _orderService = orderService;
    }
    
    [HttpPost]
    public async Task<IActionResult> Create([FromBody] CreateOrderDto dto)
    {
        var result = await _orderService.CreateOrder(dto);
        return result ? Ok() : BadRequest();
    }
}