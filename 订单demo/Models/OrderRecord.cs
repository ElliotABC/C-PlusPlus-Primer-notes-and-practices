using SqlSugar;

namespace 订单demo.Models;

public class OrderRecord
{
    public OrderRecord()
    {
        Id = SnowFlakeSingle.Instance.NextId();
    }
    [SugarColumn(IsPrimaryKey =true)]
    public long Id { get; set; } // 明细ID

    public long OrderId { get; set; } // 订单ID

    public long ProductId { get; set; } // 产品ID

    public string ProductName { get; set; } // 产品名称

    public int Quantity { get; set; } // 数量

    public decimal UnitPrice { get; set; } // 单价

    public decimal TotalPrice { get; set; } // 总价

    public string? Remark { get; set; } // 备注

    public DateTime CreateTime { get; set; } // 创建时间
    
}
