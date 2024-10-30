using System.Threading.Channels;
using ChannelApi;
using ChannelApi.HostedService;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

// 创建一个无界通道
var channel = Channel.CreateUnbounded<string>();

// 注册 ChannelWriter<string>
builder.Services.AddSingleton(channel.Writer);

// 注册 ChannelReader<string>（如果需要）
builder.Services.AddSingleton(channel.Reader);

builder.Services.AddSingleton<IChannelService, ChannelService>();
builder.Services.AddSingleton(provider => Channel.CreateUnbounded<string>());

builder.Services.AddHostedService<MessageQueue>();
var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

var summaries = new[]
{
    "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
};

app.MapGet("/weatherforecast", () =>
    {
        var forecast = Enumerable.Range(1, 5).Select(index =>
                new WeatherForecast
                (
                    DateOnly.FromDateTime(DateTime.Now.AddDays(index)),
                    Random.Shared.Next(-20, 55),
                    summaries[Random.Shared.Next(summaries.Length)]
                ))
            .ToArray();
        var writerService = app.Services.GetService<IChannelService>();
        writerService.WriteMessage("Hello World");
        return forecast;
    })
    .WithName("GetWeatherForecast")
    .WithOpenApi();

app.Run();

record WeatherForecast(DateOnly Date, int TemperatureC, string? Summary)
{
    public int TemperatureF => 32 + (int)(TemperatureC / 0.5556);
}