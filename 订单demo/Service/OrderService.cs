using 订单demo.Context;
using 订单demo.Dto;
using 订单demo.Models;
using 订单demo.Repository;

namespace 订单demo.Service;

public class OrderService : DbService, IOrderService
{
    private readonly IOrderRepository _repository;
    private readonly IProductRepository _productRepository;
    public OrderService(IOrderRepository repository, IProductRepository productRepository) : base(repository)
    {
        _repository = repository;
        _productRepository = productRepository;
    }

    public async Task<bool> CreateOrder(CreateOrderDto dto)
    {
        var order = new Order(dto.PayerId);
        order.SetRepository(_repository);
        var productsWithQuantities = new List<(Product product, int quantity)>();

        foreach (var productDto in dto.Products)
        {
            var product = await _productRepository.Get(productDto.Id);
            productsWithQuantities.Add((product, productDto.Quantity));
        }
        BeginTran();
        try
        {
            await order.CreateOrder(productsWithQuantities);
        }
        catch (Exception e)
        {
            RollbackTran();
            return false;
        }
        CommitTran();
        return true;
    }

    public async Task<List<Order>> GetPage(int pageIndex, int pageSize)
    {
        var data = await _repository.GetPage(pageIndex, pageSize);
        return data.list;
    }
}