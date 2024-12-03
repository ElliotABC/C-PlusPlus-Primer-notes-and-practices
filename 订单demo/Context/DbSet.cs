using System.Linq.Expressions;
using Serilog;
using SqlSugar;

namespace 订单demo.Context;


public class DbSet<T> : SimpleClient<T> where T : class, new()
{
    public async Task<bool> DeleteAsync(long id)
    {
        return await Context.Deleteable<T>(id).ExecuteCommandAsync() > 0;
    }

    public ISugarQueryable<T> FromMaster()
    {
        return Context.MasterQueryable<T>();
    }

    public async Task<bool> DeleteByIdsAsync(long[] ids)
    {
        return await Context.Deleteable<T>().In(ids).ExecuteCommandAsync() > 0;
    }

    public async Task<bool> InsertsAsync(List<T> data, int size)
    {
        return await Context.Fastest<T>().PageSize(size).BulkCopyAsync(data) > 0;
    }


    public virtual async Task<List<T>> GetListAsync(Expression<Func<T, bool>> whereExpression,
        params Expression<Func<T, object>>[] includes)
    {
        try
        {
            var query = BuildQuery(whereExpression, includes);
            return await query.ToListAsync();
        }
        catch (Exception e)
        {
            Log.Error(e.Message);
            throw;
        }
    }

    public virtual async Task<(long total, List<T> list)> GetListToPageAsync(Expression<Func<T, bool>> whereExpression,
        int pageIndex,
        int pageSize, Expression<Func<T, object>> orderByExpression, params Expression<Func<T, object>>[] includes)
    {
        try
        {
            var query = BuildQuery(whereExpression, includes);
            RefAsync<int> total = 0;
            var list = await query.OrderByDescending(orderByExpression).ToPageListAsync(pageIndex, pageSize, total);
            return (total, list);
        }
        catch (Exception e)
        {
            Log.Error(e.Message);
            throw;
        }
    }

    public virtual async Task<T> GetAsync(Expression<Func<T, bool>> whereExpression,
        params Expression<Func<T, object>>[] includes)
    {
        try
        {
            var query = BuildQuery(whereExpression, includes);
            return await query.FirstAsync();
        }
        catch (Exception e)
        {
            Log.Error(e.Message);
            throw;
        }
    }

    private ISugarQueryable<T> BuildQuery(Expression<Func<T, bool>> whereExpression,
        params Expression<Func<T, object>>[] includes)
    {
        var query = Context.Queryable<T>().Where(whereExpression);
        foreach (var include in includes) query = query.Includes(include);
        return query;
    }
}