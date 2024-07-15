using Accord.MachineLearning;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;
using Color = System.Drawing.Color;
using Image = SixLabors.ImageSharp.Image;

namespace k_means_gui;

public partial class Form1 : Form
{
    public Form1()
    {
        InitializeComponent();
    }

    private void Form1_Load(object sender, EventArgs e)
    {

        using (Image<Rgba32> image = Image.Load<Rgba32>("C:\\Users\\Ice\\Desktop\\bin\\Snipaste_2024-07-09_17-04-16.png"))
        {
            Rgba32[] pixels = GetPixels(image);
            double[][] data = pixels.Select(c => new double[] { c.R, c.G, c.B }).ToArray();
            int k = 5;
            KMeans kmeans = new KMeans(k);
            KMeansClusterCollection clusters = kmeans.Learn(data);
            kmeans.Clusters.Randomize(data, Seeding.Fixed);
            double[][] centroids = clusters.Centroids;
            List<PictureBox> list = new List<PictureBox>()
                { pictureBox1, pictureBox2, pictureBox3, pictureBox4, pictureBox5 };
            for (int i = 0; i < centroids.Length; i++)
            {
                Rgba32 color = new Rgba32((byte)centroids[i][0], (byte)centroids[i][1], (byte)centroids[i][2]);
                Color temp = Color.FromArgb(color.A, color.R, color.G, color.B);
                list[i].BackColor = temp;
            }
        }

    }

    private static Rgba32[] GetPixels(Image<Rgba32> image)
    {
        int width = image.Width;
        int height = image.Height;
        Rgba32[] pixels = new Rgba32[width * height];
        image.CopyPixelDataTo(pixels);
        return pixels;
    }
}