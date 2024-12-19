using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using iNKORE.UI.WPF.Modern;

namespace Launcher;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
        ThemeManager.Current.ApplicationTheme = ApplicationTheme.Dark;
    }

    private void Button_ToggleTheme_Click(object sender, RoutedEventArgs e)
    {
        if (ThemeManager.Current.ApplicationTheme == ApplicationTheme.Dark)
        {
            ThemeManager.Current.ApplicationTheme = ApplicationTheme.Light;
        }
        else
        {
            ThemeManager.Current.ApplicationTheme = ApplicationTheme.Dark;
        }
    }
}