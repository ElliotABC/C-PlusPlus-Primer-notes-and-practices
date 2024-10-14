using SqlSugar;

SqlSugarClient Db = new SqlSugarClient(new ConnectionConfig()
    {
        ConnectionString =
            "User ID=sa;pwd=+(5F9qFUt^mwGr$Z;Initial Catalog=DataLeakage;Data Source=192.168.0.180;Encrypt=True;TrustServerCertificate=True;",
        DbType = DbType.SqlServer,
        IsAutoCloseConnection = true
    },
    db => { db.Aop.OnLogExecuting = (sql, pars) => { Console.WriteLine(UtilMethods.GetNativeSql(sql, pars)); }; });

string filePath = "D:\\微博五亿2019.txt";
int blockSize = 10240 * 1024;
using (FileStream fileStream = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.Read))
{
    byte[] buffer = new byte[blockSize];
    int bytesRead;
    var tasks = new List<Task>();

    while ((bytesRead = fileStream.Read(buffer, 0, blockSize)) > 0)
    {
        Func<byte[], int, Task> taskFactory = async (chunk, length) =>
        {
            string text = System.Text.Encoding.UTF8.GetString(chunk, 0, length);
            Console.WriteLine(text);
        };
        tasks.Add(taskFactory(buffer, bytesRead));
    }
    Task.WaitAll(tasks.ToArray());
}
class WeiBo
{
    [SugarColumn(IsPrimaryKey = true)] public long uid { get; set; }
    public string phone { get; set; }
}