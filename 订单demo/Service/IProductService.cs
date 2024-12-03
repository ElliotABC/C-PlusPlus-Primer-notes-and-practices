using 订单demo.Context;
using 订单demo.Models;

namespace 订单demo.Service;

public interface IProductService : IUnitOfWork
{
    Task<bool> Create(Product product);
    Task<bool> Delete(long id);
    Task<Product> Get(long id);
}