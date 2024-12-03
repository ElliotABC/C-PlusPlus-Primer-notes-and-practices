using SqlSugar;
using 订单demo.Context;

namespace 订单demo.Extensions;

public static class SqlSugarExtension
{
    public static void AddSqlSugar(this IServiceCollection services, IConfiguration configuration)
    {
        services.AddScoped<ISqlSugarClient>(s =>
        {
            //Scoped用SqlSugarClient 
            SqlSugarClient sqlSugar = new SqlSugarClient(new ConnectionConfig()
                {
                    DbType = DbType.SqlServer,
                    ConnectionString =
                        "Server=localhost;Database=OrderDemo;User Id=sa;Password=123456;TrustServerCertificate=True;",
                    IsAutoCloseConnection = true,
                },
                db =>
                {
                    db.Aop.OnLogExecuting = (sql, pars) => { Console.WriteLine(UtilMethods.GetNativeSql(sql, pars)); };
                });
            return sqlSugar;
        });
        services.AddScoped(p => p.GetService<ISqlSugarClient>()!.CreateContext<DbContext>(false));
    }
}