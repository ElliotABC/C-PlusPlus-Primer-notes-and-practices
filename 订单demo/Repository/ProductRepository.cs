using 订单demo.Context;
using 订单demo.Models;

namespace 订单demo.Repository;

public class ProductRepository : DbRepository, IProductRepository
{
    public ProductRepository(DbContext dbContext) : base(dbContext)
    {
    }

    public async Task<long> Create(Product product)
    {
        return await DbContext.Db.Insertable(product).ExecuteReturnSnowflakeIdAsync();
    }

    public async Task<bool> Save(Product product)
    {
        return await DbContext.Db.Insertable(product).ExecuteCommandAsync() > 0;
    }

    public async Task<Product> Get(long id)
    {
        return await DbContext.Product.GetByIdAsync(id);
    }

    public async Task<bool> Delete(long id)
    {
        return await DbContext.Product.DeleteByIdAsync(id);
    }
}