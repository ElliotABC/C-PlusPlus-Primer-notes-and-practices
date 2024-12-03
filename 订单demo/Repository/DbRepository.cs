using 订单demo.Context;

namespace 订单demo.Repository;

public class DbRepository : IUnitOfWork
{
    public DbRepository(DbContext dbContext)
    {
        DbContext = dbContext;
    }

    protected DbContext DbContext { get; init; }

    public void BeginTran()
    {
        DbContext.BeginTran();
    }

    public void CommitTran()
    {
        DbContext.CommitTran();
    }

    public void RollbackTran()
    {
        DbContext.RollbackTran();
    }
}