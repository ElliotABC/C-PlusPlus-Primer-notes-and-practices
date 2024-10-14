using System.Text.RegularExpressions;
using SqlSugar;

SqlSugarClient Db = new SqlSugarClient(new ConnectionConfig()
    {
        ConnectionString =
            "PORT=3366;DATABASE=DataLeakage;HOST=192.168.0.180;PASSWORD=123456;USER ID=postgres",
        DbType = DbType.PostgreSQL,
        IsAutoCloseConnection = true
    },
    db => { db.Aop.OnLogExecuting = (sql, pars) => { Console.WriteLine(UtilMethods.GetNativeSql(sql, pars)); }; });

var batch = new List<QQ>();
using (var reader = new StreamReader("D:\\数据泄漏\\6.9更新总库.txt"))
{
    string line;
    while ((line = reader.ReadLine()) != null)
    {
        try
        {
            string pattern = @"\d+";
            MatchCollection matches = Regex.Matches(line, pattern);
            batch.Add(new QQ()
            {
                qid = Convert.ToInt64(matches[0].Value),
                phone = matches[1].Value
            });
            if (batch.Count == 10240)
            {
                Db.Fastest<QQ>().BulkCopy(batch);
                batch.Clear();
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
            continue;
        }
    }
}

// 写入剩余的数据
if (batch.Any())
{
    Db.Fastest<QQ>().BulkCopy(batch);
}

[SugarTable("public.qq", "qq")]
class QQ
{
    [SugarColumn(IsPrimaryKey = true)] public long qid { get; set; }
    public string phone { get; set; }
}