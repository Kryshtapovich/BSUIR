using System;
using System.IO;
using System.Text;

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

            MemoryStream memoryfile = new MemoryStream(byteArray);
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

        private void WriteFile(Stream source, string path)
        {
            using (var file = new FileStream(path, FileMode.Create))
            {
                source.CopyTo(file);
            }
        }

        public void Send(string xmlContent, string xsdContent)
        {
            var xmlFile = CreateMemoryFile(xmlContent);

            var xsdFile = CreateMemoryFile(xsdContent);

            CreatePaths();
            DirectoryInfo directory = Directory.CreateDirectory(directoryPath);

            WriteFile(xmlFile, xmlPath);
            WriteFile(xsdFile, xsdPath);
        }

    }
}
