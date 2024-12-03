namespace 订单demo.Context;

public interface IUnitOfWork
{
    public void BeginTran();

    public void CommitTran();

    public void RollbackTran();

}