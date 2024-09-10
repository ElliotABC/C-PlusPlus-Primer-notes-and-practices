using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

DateTime startTime = DateTime.Now;
using (Image<Rgba32> image = Image.Load<Rgba32>("C:\\Users\\Ice\\Desktop\\bin\\ConsoleApp1\\壁纸1.jpg"))
{
    // 遍历每个像素，颠倒RGB通道
    for (int y = 0; y < image.Height; y++)
    {
        for (int x = 0; x < image.Width; x++)
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
using (Image<Rgba32> image = Image.Load<Rgba32>("C:\\Users\\Ice\\Desktop\\bin\\ConsoleApp1\\壁纸1.jpg"))
{
    Parallel.For(0, image.Height, y =>
    {
        for (int x = 0; x < image.Width; x++)
        {
            Rgba32 pixel = image[x, y];
            image[x, y] = new Rgba32(pixel.B, pixel.G, pixel.R, pixel.A);
        }
    });
    // 保存颠倒后的图像
    image.Save("C:\\Users\\Ice\\Desktop\\new_并行处理.jpg");
}
endTime = DateTime.Now;
Console.WriteLine(endTime - startTime);
Console.WriteLine("并行处理结束");