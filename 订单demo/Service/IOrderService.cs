using 订单demo.Dto;
using 订单demo.Models;

namespace 订单demo.Service;

public interface IOrderService
{
    Task<bool> CreateOrder(CreateOrderDto dto);

    Task<List<Order>> GetPage(int pageIndex, int pageSize);
    
    Task<bool> AddOrUpdateProduct(AddOrUpdateProductDto dto);
}