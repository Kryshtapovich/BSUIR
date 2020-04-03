using Models;
using System.IO;
using System.IO.Compression;
using System.Threading.Tasks;

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

        public async Task ArchiveAsync(string directoryPath)
        {
            await Task.Run(async () =>
            {
                await Task.Delay(100);
                var files = Directory.GetFiles(directoryPath);
                string zipDirectory = Path.Combine(archiveFolder, Path.GetFileName(directoryPath) + "_encrypted");
                Directory.CreateDirectory(zipDirectory);
                foreach (var file in files)
                {
                    await encryptor.EncryptAsync(file, zipDirectory);
                }

                ZipFile.CreateFromDirectory(zipDirectory, zipDirectory + ".zip");
                Directory.Delete(zipDirectory, true);
            });
        }

        public async Task DearchiveAsync(string directoryPath)
        {
            await Task.Run(async () =>
            {
                string extractDirectory = Path.Combine(extractFolder,
                    Path.GetFileName(directoryPath).Replace("DEARCHIVE", "")
                    .Replace("_encrypted.zip", "_decrypted"));

                ZipFile.ExtractToDirectory(directoryPath, extractDirectory);

                var files = Directory.GetFiles(extractDirectory);
                foreach (var file in files)
                {
                    await encryptor.DecryptAsync(file, extractDirectory);
                    File.Delete(file);
                }
            });
        }
    }
}
