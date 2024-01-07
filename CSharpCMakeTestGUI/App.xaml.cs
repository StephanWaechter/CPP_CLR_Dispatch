using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using System.Windows;

namespace CSharpCMakeTestGUI
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void Application_Startup(object sender, StartupEventArgs e)
        {
            var device_service = new Services.ThreadSafeDeviceService();
            var window = new MainWindow
            {
                DataContext = new ViewModels.MainViewModel(device_service)
            };
            window.Show();
        }
    }
}
