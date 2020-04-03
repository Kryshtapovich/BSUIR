using System;
using System.ServiceProcess;
using System.Windows;

namespace LR2_Monitor
{
    static class MyService
    {
        private static string service = "MyService";

        private static object obj = new object();

        private static ServiceController controller = new ServiceController(service);

        public static void StartService()
        {
            if (controller.Status != ServiceControllerStatus.Running)
            {

                controller.Start();
                controller.WaitForStatus(ServiceControllerStatus.Running, TimeSpan.FromMinutes(1));
                ShowMessage("was succesfully launched", "Start");
            }
            else
            {
                ShowMessage("is already running", "Error");
            }
        }

        public static void StopService()
        {
            if (controller.Status != ServiceControllerStatus.Stopped)
            {
                controller.Stop();
                controller.WaitForStatus(ServiceControllerStatus.Stopped, TimeSpan.FromMinutes(1));
                ShowMessage("was successfully stopped", "Stop");
            }
            else
            {
                ShowMessage("is already stopped", "Error");
            }
        }

        private static void ShowMessage(string eventDescription, string serviceEvent)
        {
            MessageBox.Show($"The service {eventDescription}", $"{serviceEvent}", MessageBoxButton.OK, MessageBoxImage.Information);
        }
    }
}
