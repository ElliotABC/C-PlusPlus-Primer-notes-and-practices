using SqlSugar;
using 订单demo.Repository;

namespace 订单demo.Models;

public class Product
{
    public Product()
    {
        CreateTime = DateTime.Now;
    }

    public IProductRepository ProductRepository;

    [SugarColumn(IsPrimaryKey =true)]
    public long Id { get; set; }

    public string Name { get; set; }

    public decimal Price { get; set; }

    public DateTime CreateTime { get; set; }

    public string Remark { get; set; }
    
    public async Task<long> Create()
    {
        return await ProductRepository.Create(this);
    }
    
    public void SetRepository(IProductRepository repository)
    {
        ProductRepository = repository;
    }
}