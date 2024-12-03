namespace 订单demo.Dto;

public class CreateOrderDto
{
    public long PayerId { get; set; }
    public List<ProductDto> Products { get; set; }
}

/// <summary>
///  下单商品dto
/// </summary>
public class ProductDto
{
    /// <summary>
    ///  商品id
    /// </summary>
    public long Id { get; set; }
    /// <summary>
    ///     数量
    /// </summary>
    public int Quantity { get; set; } 
}