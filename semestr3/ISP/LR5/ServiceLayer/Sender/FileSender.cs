using System;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace ServiceLayer
{
    public class FileSender : ISender
    {
        private readonly string targetDirectory;

        private string directoryPath;

        private string xmlPath;

        private string xsdPath;

        public FileSender(string targetDirPath)
        {
            targetDirectory = targetDirPath;
        }

        private Stream CreateMemoryFile(string content)
        {
            byte[] byteArray = Encoding.UTF8.GetBytes(content);

            var memoryfile = new MemoryStream(byteArray);
            memoryfile.Position = 0;

            return memoryfile;
        }

        private void CreatePaths()
        {
            string date = DateTime.Now.ToString().Replace(":", ".");
            directoryPath = Path.Combine(targetDirectory, date);
            xmlPath = Path.Combine(directoryPath, date) + ".xml";
            xsdPath = Path.Combine(directoryPath, date) + ".xsd";
        }

        private async Task WriteFileAsync(Stream source, string path)
        {
            using (var file = new FileStream(path, FileMode.Create))
            {
                await source.CopyToAsync(file);
            }
            source.Close();
            source.Dispose();
        }

        public async Task SendAsync(string xmlContent, string xsdContent)
        {
            var xmlFile = CreateMemoryFile(xmlContent);

            var xsdFile = CreateMemoryFile(xsdContent);

            CreatePaths();
            var directory = Directory.CreateDirectory(directoryPath);

            await WriteFileAsync(xmlFile, xmlPath);
            await WriteFileAsync(xsdFile, xsdPath);
        }

    }
}
