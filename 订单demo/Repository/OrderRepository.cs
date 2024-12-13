using SqlSugar;
using 订单demo.Context;
using 订单demo.Models;

namespace 订单demo.Repository;

public class OrderRepository : DbRepository, IOrderRepository
{
    public OrderRepository(DbContext dbContext) : base(dbContext)
    {
    }

    public async Task<bool> CreateOrder(Order order)
    {
        return await DbContext.Orders.InsertAsync(order);
    }

    public async Task<bool> Record(List<OrderRecord> records)
    {
        return await DbContext.OrderRecode.InsertsAsync(records, records.Count);
    }

    public async Task<bool> Save(Order order)
    {
        try
        {
            return await DbContext.Orders.InsertOrUpdateAsync(order);
        }
        catch (VersionExceptions ex)
        {
            return false;
        }
    }

    public async Task<(long total, List<Order> list)> GetPage(int pageIndex, int pageSize)
    {
        return await DbContext.Orders.GetListToPageAsync(it => it.Id > 0, pageIndex, pageSize, it => it.CreateTime);
    }

    public async Task<Order> GetOrder(long orderId)
    {
        var reslut = await DbContext.Orders.GetAsync(it => it.Id == orderId);
        reslut.SetRepository(this);
        return reslut;
    }
}