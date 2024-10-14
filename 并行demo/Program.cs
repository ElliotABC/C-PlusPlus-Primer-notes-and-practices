using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

DateTime startTime = DateTime.Now;
using (Image<Rgba32> image = Image.Load<Rgba32>("C:\\Users\\Ice\\Desktop\\bin\\ConsoleApp1\\湿润兔『妄想病栋』09.jpg"))
{
    // 获取图像的宽度和高度  
    int width = image.Width;
    int height = image.Height;

    // 遍历每个像素，颠倒RGB通道  
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Rgba32 pixel = image[x, y];
            image[x, y] = new Rgba32(pixel.B, pixel.G, pixel.R, pixel.A);
        }
    }

    // 保存颠倒后的图像  
    image.Save("C:\\Users\\Ice\\Desktop\\new_image.jpg");
}

DateTime endTime = DateTime.Now;
Console.WriteLine(endTime - startTime);
Console.WriteLine("单线程处理结束");
startTime = DateTime.Now;
using (Image<Rgba32> image = Image.Load<Rgba32>("C:\\Users\\Ice\\Desktop\\bin\\ConsoleApp1\\湿润兔『妄想病栋』09.jpg"))
{
    Parallel.For(0, image.Height, y =>
    {
        for (int x = 0; x < image.Width; x++)
        {
            Rgba32 pixel = image[x, y];
            image[x, y] = new Rgba32(pixel.B, pixel.G, pixel.R, pixel.A);
        }
    }); // 保存颠倒后的图像  
    image.Save("C:\\Users\\Ice\\Desktop\\new_并行处理.jpg");
    

}

endTime = DateTime.Now;
Console.WriteLine(endTime - startTime);
Console.WriteLine("并行处理结束");

using (Image<Rgba32> image = Image.Load<Rgba32>("C:\\Users\\Ice\\Desktop\\bin\\ConsoleApp1\\湿润兔『妄想病栋』09.jpg"))
{
    var tasksFactory = new TaskFactory();
    var task = new Task[image.Height];
    for (int y = 0; y < image.Height; y++)
    {
        task[y] = tasksFactory.StartNew(() =>
        {
            for (int x = 0; x < image.Width; x++)
            {
                Rgba32 pixel = image[x, y];
                image[x, y] = new Rgba32(pixel.B, pixel.G, pixel.R, pixel.A);
            }
        });
    }
    Task.WaitAll(task);

}

endTime = DateTime.Now;
Console.WriteLine(endTime - startTime);
Console.WriteLine("并行处理结束");