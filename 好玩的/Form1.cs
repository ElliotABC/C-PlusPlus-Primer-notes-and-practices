namespace 好玩的
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            StartPosition = FormStartPosition.CenterScreen;
            BackColor = Color.White;
            TransparencyKey = Color.White;
            pictureBox1.BackColor = TransparencyKey;
        }
    }
}
