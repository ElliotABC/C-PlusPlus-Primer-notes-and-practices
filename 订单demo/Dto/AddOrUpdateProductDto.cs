namespace 订单demo.Dto;

public class AddOrUpdateProductDto
{
    public long OrderId { get; set; }
    public List<ProductDto> Products { get; set; }
}