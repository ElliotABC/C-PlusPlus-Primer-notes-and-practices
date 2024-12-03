using SqlSugar;
using 订单demo.Models;

namespace 订单demo.Context;


public class DbContext : SugarUnitOfWork, IUnitOfWork
{
    public virtual void BeginTran()
    {
        Db.Ado.BeginTran();
    }

    public virtual void CommitTran()
    {
        Db.Ado.CommitTran();
    }

    public virtual void RollbackTran()
    {
        Db.Ado.RollbackTran();
    }
    
    public DbSet<Order> Orders { get; set; }
    public DbSet<OrderRecord> OrderRecode { get; set; }
    public DbSet<Product> Product { get; set; }
}