using 订单demo.Context;
using 订单demo.Models;

namespace 订单demo.Repository;

public interface IOrderRepository : IUnitOfWork
{
    Task<bool> CreateOrder(Order order);

    Task<bool> Record(List<OrderRecord> records);

    Task<bool> Save(Order order);
    
    Task<(long total, List<Order> list)> GetPage(int pageIndex, int pageSize);
}