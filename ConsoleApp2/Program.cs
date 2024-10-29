using Microsoft.EntityFrameworkCore;
using System.ComponentModel.DataAnnotations;
using System.Text.Json;
using System.Text.RegularExpressions;


public class AppDbContext : DbContext
{
    public DbSet<SampleType> SampleTypes { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseSqlServer("Server=localhost;Database=DDDEF;User Id=sa;Password=123456;TrustServerCertificate=True;");
    }

    // 查询订单
    public SampleType GetById(int id)
    {
        return SampleTypes
            .Include(o => o.Children)
            .SingleOrDefault(o => o.Id == id);
    }
    
    public List<SampleType> GetAll()
    {
        return SampleTypes
            .Include(o => o.Children)
            .ToList();
    }

    public List<SampleType> GetSampleTypes()
    {
        return SampleTypes
            .Include(o => o.Children)
            .Where(o => o.ParentId == 0)
            .ToList();
    }
}


class Program
{
    static void Main()
    {
        // 创建数据库
        using (var context = new AppDbContext())
        {
            context.Database.EnsureDeleted();
            context.Database.EnsureCreated();
        }

        // 创建产品
        var sampleType = new SampleType { ParentId = 0, Name = "Parent"};
        var sampleType2 = new SampleType { ParentId = 0, Name = "Parent2"};
        var child1 = new SampleType { ParentId = 1, Name = "Child 1"};
        var child2 = new SampleType { ParentId = 1, Name = "Child 2"};

        var child3 = new SampleType { ParentId = 2, Name = "Child 1"};
        var child4 = new SampleType { ParentId = 2, Name = "Child 2"};
        
        sampleType.Children.Add(child1);
        sampleType.Children.Add(child2);
        
        sampleType2.Children.Add(child3);
        sampleType2.Children.Add(child4);
        using (var context = new AppDbContext())
        {
            context.SampleTypes.Add(sampleType);    
            context.SampleTypes.Add(sampleType2);    
            context.SaveChanges();
        }

        using (var context = new AppDbContext())
        {
            var data = context.GetSampleTypes();
            Console.WriteLine(Regex.Unescape(JsonSerializer.Serialize(data)));
        }
    }
    
}

public class SampleType
{
    [Key]
    public int Id { get; set; }
    public int ParentId { get; set; }
    public string Name { get; set; }
    public List<SampleType> Children { get; set; } = new();
}