using System;
using System.Windows;

namespace LR2_Monitor
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Monitor sourceMonitor = new Monitor(sourceDir.Text);
                Monitor archiveMonitor = new Monitor(archiveDir.Text);
                Monitor extractMonitor = new Monitor(extractDir.Text);
                sourceMonitor.StartMonitoring();
                archiveMonitor.StartMonitoring();
                extractMonitor.StartMonitoring();
                MyService.StartService();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void MainWindow1_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            MyService.StopService();
        }
    }
}
