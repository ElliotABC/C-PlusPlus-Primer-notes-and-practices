using System.Text.Json.Serialization;
using Serilog;
using 订单demo.Extensions;
using 订单demo.Repository;
using 订单demo.Service;
using ILogger = Serilog.ILogger;

var builder = WebApplication.CreateBuilder(args);
Log.Logger = ConfigurateLogger(builder.Configuration);
try
{
    builder.Services.AddEndpointsApiExplorer();
    builder.Services.AddSwaggerGen();
    builder.Services.AddHttpContextAccessor();
    builder.Services.AddSerilog(dispose: true);
    builder.Services.AddSqlSugar(builder.Configuration);
    builder.Services.AddControllers().AddJsonOptions(options =>
    {
        options.JsonSerializerOptions.Converters.Add(new JsonStringEnumConverter());
    });

    #region ioc
    builder.Services.AddScoped<IProductRepository, ProductRepository>();
    builder.Services.AddScoped<IOrderRepository, OrderRepository>();
    builder.Services.AddScoped<IProductService, ProductService>();
    builder.Services.AddScoped<IOrderService, OrderService>();
    #endregion
    
    var app = builder.Build();

    if (app.Environment.IsDevelopment())
    {
        app.UseSwagger();
        app.UseSwaggerUI();
    }

    app.UseHttpsRedirection();
    app.MapControllers();
    app.Run();
}
catch (Exception ex)
{
    Log.Fatal(ex, "服务意外终止：" + ex.Message);
}
finally
{
    Log.CloseAndFlush();
}

static ILogger ConfigurateLogger(ConfigurationManager configuration)
{
    return new LoggerConfiguration().ReadFrom.Configuration(configuration)
        .CreateLogger(); //清除内置日志框架
}