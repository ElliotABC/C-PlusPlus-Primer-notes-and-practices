namespace k_means_gui;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    ///  Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }

        base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    ///  Required method for Designer support - do not modify
    ///  the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        pictureBox1 = new PictureBox();
        pictureBox2 = new PictureBox();
        pictureBox3 = new PictureBox();
        pictureBox4 = new PictureBox();
        pictureBox5 = new PictureBox();
        ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
        ((System.ComponentModel.ISupportInitialize)pictureBox2).BeginInit();
        ((System.ComponentModel.ISupportInitialize)pictureBox3).BeginInit();
        ((System.ComponentModel.ISupportInitialize)pictureBox4).BeginInit();
        ((System.ComponentModel.ISupportInitialize)pictureBox5).BeginInit();
        SuspendLayout();
        // 
        // pictureBox1
        // 
        pictureBox1.BackColor = SystemColors.ControlLight;
        pictureBox1.Location = new Point(12, 3);
        pictureBox1.Name = "pictureBox1";
        pictureBox1.Size = new Size(100, 50);
        pictureBox1.TabIndex = 0;
        pictureBox1.TabStop = false;
        // 
        // pictureBox2
        // 
        pictureBox2.BackColor = SystemColors.ControlLight;
        pictureBox2.Location = new Point(118, 3);
        pictureBox2.Name = "pictureBox2";
        pictureBox2.Size = new Size(100, 50);
        pictureBox2.TabIndex = 1;
        pictureBox2.TabStop = false;
        // 
        // pictureBox3
        // 
        pictureBox3.BackColor = SystemColors.ControlLight;
        pictureBox3.Location = new Point(224, 3);
        pictureBox3.Name = "pictureBox3";
        pictureBox3.Size = new Size(100, 50);
        pictureBox3.TabIndex = 2;
        pictureBox3.TabStop = false;
        // 
        // pictureBox4
        // 
        pictureBox4.BackColor = SystemColors.ControlLight;
        pictureBox4.Location = new Point(330, 3);
        pictureBox4.Name = "pictureBox4";
        pictureBox4.Size = new Size(100, 50);
        pictureBox4.TabIndex = 3;
        pictureBox4.TabStop = false;
        // 
        // pictureBox5
        // 
        pictureBox5.BackColor = SystemColors.ControlLight;
        pictureBox5.Location = new Point(436, 3);
        pictureBox5.Name = "pictureBox5";
        pictureBox5.Size = new Size(100, 50);
        pictureBox5.TabIndex = 4;
        pictureBox5.TabStop = false;
        // 
        // Form1
        // 
        AutoScaleDimensions = new SizeF(7F, 17F);
        AutoScaleMode = AutoScaleMode.Font;
        ClientSize = new Size(800, 450);
        Controls.Add(pictureBox5);
        Controls.Add(pictureBox4);
        Controls.Add(pictureBox3);
        Controls.Add(pictureBox2);
        Controls.Add(pictureBox1);
        Name = "Form1";
        Text = "Form1";
        Load += Form1_Load;
        ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
        ((System.ComponentModel.ISupportInitialize)pictureBox2).EndInit();
        ((System.ComponentModel.ISupportInitialize)pictureBox3).EndInit();
        ((System.ComponentModel.ISupportInitialize)pictureBox4).EndInit();
        ((System.ComponentModel.ISupportInitialize)pictureBox5).EndInit();
        ResumeLayout(false);
    }

    #endregion

    private PictureBox pictureBox1;
    private PictureBox pictureBox2;
    private PictureBox pictureBox3;
    private PictureBox pictureBox4;
    private PictureBox pictureBox5;
}