using System;
using System.IO;
using System.Windows;

namespace LR2_Monitor
{
    class Monitor
    {
        private readonly FileSystemWatcher monitor;

        public Monitor(string dirName)
        {
            monitor = new FileSystemWatcher(dirName);
            monitor.Created += Monitor_Created;
            monitor.Deleted += Monitor_Deleted;
        }

        public void StartMonitoring()
        {
            monitor.EnableRaisingEvents = true;
        }

        public void StopMonitoring()
        {
            monitor.EnableRaisingEvents = false;
        }

        private void Monitor_Deleted(object sender, FileSystemEventArgs e)
        {
            ShowChanges("deleted", e.FullPath);
        }

        private void Monitor_Created(object sender, FileSystemEventArgs e)
        {
            ShowChanges("added", e.FullPath);
        }

        private void ShowChanges(string fileEvent, string filePath)
        {
            MessageBox.Show($"{DateTime.Now:dd/MM/yyyy HH:mm:ss} file {filePath} was {fileEvent}", Path.GetDirectoryName(filePath),
                MessageBoxButton.OK, MessageBoxImage.Information);
        }
    }
}
