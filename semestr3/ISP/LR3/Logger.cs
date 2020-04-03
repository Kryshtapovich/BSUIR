using System.Collections.Generic;
using System.IO;
using System.Threading;

namespace LR2
{
    class Logger
    {
        private readonly FileSystemWatcher sourceWatcher;

        private readonly FileSystemWatcher archiveWatcher;

        private List<Folder> folders;

        private bool enabled = true;

        public Logger(ConfigurationOptions options, string errorFile)
        {
            this.folders = options.Folders;
            Encryptor.GetCryptoOptions(options.CryptoOption.Key, options.CryptoOption.Vector);
            Archivator.ErrorFile = errorFile;
            sourceWatcher = new FileSystemWatcher(folders.Find(x => x.Name == "Source").Path);
            archiveWatcher = new FileSystemWatcher(folders.Find(x => x.Name == "Archive").Path);
            sourceWatcher.Created += SourceWatcher_Created;
            archiveWatcher.Renamed += TargetWatcher_Renamed;
        }

        public void Start()
        {
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

        private void SourceWatcher_Created(object sender, FileSystemEventArgs e)
        {
            Archivator.Archive(e.FullPath, folders.Find(x => x.Name == "Archive").Path);
        }

        private void TargetWatcher_Renamed(object sender, RenamedEventArgs e)
        {
            if (Path.GetFileNameWithoutExtension(e.FullPath).Contains("DEARCHIVE"))
            {
                Archivator.Dearchive(e.FullPath, folders.Find(x => x.Name == "Extract").Path);
                File.Delete(e.FullPath);
            }
        }
    }
}