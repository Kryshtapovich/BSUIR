using System;
using System.IO;
using System.Threading;
using Models;

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
            sourceWatcher.Created += SourceWatcher_Created;
            archiveWatcher.Renamed += TargetWatcher_Renamed;
        }

        public void Start()
        {
            sourceWatcher.EnableRaisingEvents = true;
            sourceWatcher.IncludeSubdirectories = false;
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

        private void SourceWatcher_Created(object sender, FileSystemEventArgs e)
        {
            try
            {
                archivator.Archive(e.FullPath);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void TargetWatcher_Renamed(object sender, RenamedEventArgs e)
        {
            try
            {
                if (Path.GetFileNameWithoutExtension(e.FullPath).Contains("DEARCHIVE"))
                {
                    archivator.Dearchive(e.FullPath);
                }
            }
            catch(Exception ex)
            {
                throw ex;
            }
        }
    }
}
