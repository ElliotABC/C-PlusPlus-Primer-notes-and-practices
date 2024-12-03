using SqlSugar;
using 订单demo.Repository;

namespace 订单demo.Models;

public class Order
{
    public Order()
    {
        
    }
    public Order(long payerId)
    {
        Id = SnowFlakeSingle.Instance.NextId();
        CreateTime = DateTime.Now;
        Status = OrderStatus.Created; // 默认状态为Created
        PayerId = payerId;
    }
    public IOrderRepository OrderRepository { get; set; }
    
    [SugarColumn(IsPrimaryKey =true)]
    public long Id { get; set; }
    
    public decimal Price { get; set; }
    
    public DateTime CreateTime { get; set; }
    
    public OrderStatus Status { get; set; }
    
    public string Remark { get; set; }
    
    public long PayerId { get; set; }

    public async Task<Order> CreateOrder(List<(Product product, int quantity)> productsWithQuantities)
    {
        if (productsWithQuantities == null || !productsWithQuantities.Any())
        {
            throw new ArgumentException("Products list cannot be empty.");
        }

        // 计算订单总价
        Price = productsWithQuantities.Sum(p => p.product.Price * p.quantity);

        // 创建订单记录
        var orderRecordList = new List<OrderRecord>();
        foreach (var (product, quantity) in productsWithQuantities)
        {
            var orderRecord = new OrderRecord
            {
                OrderId = Id,
                ProductId = product.Id,
                ProductName = product.Name,
                Quantity = quantity,
                UnitPrice = product.Price,
                TotalPrice = product.Price * quantity,
                CreateTime = DateTime.Now,
                Remark = product.Remark
            };
            orderRecordList.Add(orderRecord);
        }

        // 保存订单
        await Create();
        
        // 保存订单明细
        await Record(orderRecordList);

        return this;
    }
    
    public void SetRepository(IOrderRepository repository)
    {
        OrderRepository = repository;
    }
    
    private async Task Record(List<OrderRecord> records)
    {
        await OrderRepository.Record(records);
    }

    private async Task Save()
    {
        await OrderRepository.Save(this);
    }

    private async Task Create()
    {
        await OrderRepository.CreateOrder(this);
    }
}

public enum OrderStatus
{
    // 创建
    Created,
    // 支付
    Paid,
    // 完成
    Completed,
    // 取消
    Canceled
}