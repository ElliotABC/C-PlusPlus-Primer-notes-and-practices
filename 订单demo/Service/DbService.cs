using 订单demo.Context;

namespace 订单demo.Service;

public class DbService : IUnitOfWork
{
    public DbService(IUnitOfWork uow)
    {
        Uow = uow;
    }

    protected IUnitOfWork Uow { get; init; }

    public void BeginTran()
    {
        Uow.BeginTran();
    }

    public void CommitTran()
    {
        Uow.CommitTran();
    }

    public void RollbackTran()
    {
        Uow.RollbackTran();
    }
}