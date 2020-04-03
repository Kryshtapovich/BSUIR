using System;
using System.IO;
using System.Threading;
using System.Threading.Tasks;

namespace LR2
{
    class Logger
    {
        private readonly FileSystemWatcher sourceWatcher;

        private readonly FileSystemWatcher targetWatcher;

        private readonly string sourceDirPath = @"E:\LR2_Service\source";

        private readonly string targetDirPath = @"E:\LR2_Service\archive";

        private readonly string extractDirPath = @"E:\LR2_Service\extract";

        private bool enabled = true;

        public Logger()
        {
            sourceWatcher = new FileSystemWatcher(sourceDirPath);
            targetWatcher = new FileSystemWatcher(targetDirPath);
            sourceWatcher.Created += SourceWatcher_Created;
            targetWatcher.Renamed += TargetWatcher_Renamed;
        }

        public void Start()
        {
            sourceWatcher.EnableRaisingEvents = true;
            targetWatcher.EnableRaisingEvents = true;
            while (enabled)
            {
                Thread.Sleep(1000);
            }
        }

        public void Stop()
        {
            sourceWatcher.EnableRaisingEvents = false;
            targetWatcher.EnableRaisingEvents = false;
            enabled = false;
        }

        private void SourceWatcher_Created(object sender, FileSystemEventArgs e)
        {
            Archivator.Archive(e.FullPath, targetDirPath);
        }

        private void TargetWatcher_Renamed(object sender, RenamedEventArgs e)
        {
            if (Path.GetFileNameWithoutExtension(e.FullPath).Contains("DEARCHIVE"))
            {
                Archivator.Dearchive(e.FullPath, extractDirPath);
                File.Delete(e.FullPath);
            }
        }
    }
}