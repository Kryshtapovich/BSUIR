using System.IO;
using System.IO.Compression;
using System.Threading;
using Models;

namespace FileManager
{
    class Archivator
    {
        private readonly string archiveFolder;

        private readonly string extractFolder;

        private readonly Encryptor encryptor;

        public Archivator(FileManagerOptions options)
        {
            archiveFolder = options["Archive"];
            extractFolder = options["Extract"];
            encryptor = new Encryptor();
        }

        public void Archive(string directoryPath)
        {
            Thread.Sleep(1000);
            var files = Directory.GetFiles(directoryPath);
            string zipDirectory = Path.Combine(archiveFolder, Path.GetFileName(directoryPath) + "_encrypted");
            Directory.CreateDirectory(zipDirectory);
            foreach (var file in files)
            {
                encryptor.Encrypt(file, zipDirectory);
            }

            Thread.Sleep(100);
            ZipFile.CreateFromDirectory(zipDirectory, zipDirectory + ".zip");
            Directory.Delete(zipDirectory, true);
        }

        public void Dearchive(string directoryPath)
        {
            string extractDirectory = Path.Combine(extractFolder,
                Path.GetFileName(directoryPath).Replace("DEARCHIVE", "")
                .Replace("_encrypted.zip", "_decrypted"));

            ZipFile.ExtractToDirectory(directoryPath, extractDirectory);

            var files = Directory.GetFiles(extractDirectory);
            foreach (var file in files)
            {
                encryptor.Decrypt(file, extractDirectory);
                File.Delete(file);
            }
        }
    }
}
