using Microsoft.AspNetCore.Mvc;
using 订单demo.Models;
using 订单demo.Service;

namespace 订单demo.Controllers;

public class ProductController : BaseController
{
    private readonly IProductService _productService;
    public ProductController(IProductService productService)
    {
        _productService = productService;
    }
    
    [HttpPost]
    public async Task<IActionResult> Create(Product product)
    {
        return Ok(await _productService.Create(product));
    }
}