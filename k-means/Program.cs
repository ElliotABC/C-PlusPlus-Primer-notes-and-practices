using Accord.MachineLearning;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

using (Image<Rgba32> image = Image.Load<Rgba32>("C:\\Users\\Ice\\Desktop\\8F76AEC37E660A2A48AD5C0A4EA18B5E.jpg"))
{
    int seed = 42;
    Rgba32[] pixels = GetPixels(image);
    double[][] data = pixels.Select(c => new double[] { c.R, c.G, c.B }).ToArray();
    int k = 5;
    KMeans kmeans = new KMeans(k);
    kmeans.UseSeeding = Seeding.Fixed;
    KMeansClusterCollection clusters = kmeans.Learn(data);
    double[][] centroids = clusters.Centroids;
    for (int i = 0; i < centroids.Length; i++)
    {
        Rgba32 color = new Rgba32((byte)centroids[i][0], (byte)centroids[i][1], (byte)centroids[i][2]);
        Console.WriteLine($"主题色 {i + 1}: RGB({color.R}, {color.G}, {color.B})");
    }
}

static Rgba32[] GetPixels(Image<Rgba32> image)
{
    int width = image.Width;
    int height = image.Height;
    Rgba32[] pixels = new Rgba32[width * height];
    image.CopyPixelDataTo(pixels);
    return pixels;
}