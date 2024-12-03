using 订单demo.Context;
using 订单demo.Models;
using 订单demo.Repository;

namespace 订单demo.Service;

public class ProductService : DbService, IProductService
{
    private readonly IProductRepository _productRepository;
    public ProductService(IProductRepository repository) : base(repository)
    {
        _productRepository = repository;
    }

    public async Task<bool> Create(Product product)
    {
        product.SetRepository(_productRepository);
        return await product.Create() > 0;
    }

    public async Task<bool> Delete(long id)
    {
        return await _productRepository.Delete(id);
    }

    public async Task<Product> Get(long id)
    {
        return await _productRepository.Get(id);
    }
}