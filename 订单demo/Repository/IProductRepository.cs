using 订单demo.Context;
using 订单demo.Models;

namespace 订单demo.Repository;

public interface IProductRepository : IUnitOfWork
{
    Task<long> Create(Product product);
    Task<bool> Save(Product product);
    Task<Product> Get(long id);
    Task<bool> Delete(long id);
}