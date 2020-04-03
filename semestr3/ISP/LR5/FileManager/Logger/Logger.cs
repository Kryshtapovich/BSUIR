using Models;
using System.IO;
using System.Threading;

namespace FileManager
{
    class Logger
    {
        private readonly FileSystemWatcher sourceWatcher;

        private readonly FileSystemWatcher archiveWatcher;

        private readonly Archivator archivator;

        private bool enabled = true;

        public Logger(FileManagerOptions options)
        {
            archivator = new Archivator(options);
            sourceWatcher = new FileSystemWatcher(options["Source"]);
            archiveWatcher = new FileSystemWatcher(options["Archive"]);
            sourceWatcher.Created += SourceWatcher_CreatedAsync;
            archiveWatcher.Renamed += TargetWatcher_RenamedAsync;
        }

        public void Start()
        {
            sourceWatcher.IncludeSubdirectories = false;
            sourceWatcher.EnableRaisingEvents = true;
            archiveWatcher.EnableRaisingEvents = true;
            while (enabled)
            {
                Thread.Sleep(1000);
            }
        }

        public void Stop()
        {
            sourceWatcher.EnableRaisingEvents = false;
            archiveWatcher.EnableRaisingEvents = false;
            enabled = false;
        }

        private async void SourceWatcher_CreatedAsync(object sender, FileSystemEventArgs e)
        {
            await archivator.ArchiveAsync(e.FullPath);
        }

        private async void TargetWatcher_RenamedAsync(object sender, RenamedEventArgs e)
        {
            if (Path.GetFileNameWithoutExtension(e.FullPath).Contains("DEARCHIVE"))
            {
                await archivator.DearchiveAsync(e.FullPath);
            }
        }
    }
}
