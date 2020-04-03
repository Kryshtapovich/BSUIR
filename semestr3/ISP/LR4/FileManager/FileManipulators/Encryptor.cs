using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace FileManager
{
    class Encryptor
    {
        private readonly DESCryptoServiceProvider crypto = new DESCryptoServiceProvider
        {
            Key = Encoding.UTF8.GetBytes("Mishanya"),
            IV = Encoding.UTF8.GetBytes("Mishanya")
        };

        private string GenerateNewName(string oldName, string folder, string extension)
        {

            string name = Path.GetFileNameWithoutExtension(oldName);
            name += extension + Path.GetExtension(oldName);
            string newName = oldName.Replace(Path.GetFileName(oldName), name);
            newName = newName.Replace(Path.GetDirectoryName(newName), folder);
            return newName;
        }

        public void Encrypt(string sourceFile, string folder)
        {
            string targetFile = GenerateNewName(sourceFile, folder, "_encrypted");

            FileStream sourceStream;
            while (true)
            {
                try
                {
                    sourceStream = new FileStream(sourceFile, FileMode.Open);
                }
                catch (IOException)
                {
                    continue;
                }
                break;
            }

            using (var targetStream = new FileStream(targetFile, FileMode.Create))
            {
                using (var ecStream = new CryptoStream(targetStream, crypto.CreateEncryptor(),
                    CryptoStreamMode.Write))
                {
                    sourceStream.CopyTo(ecStream);
                }
            }
            sourceStream.Close();
            sourceStream.Dispose();
        }

        public void Decrypt(string sourceFile, string folder)
        {
            string targetFile = GenerateNewName(sourceFile.Replace("_encrypted", ""), folder, "_decrypted");

            using (var sourceStream = new FileStream(sourceFile, FileMode.Open))
            {
                using (var targetStream = new FileStream(targetFile, FileMode.Create))
                {
                    using (var deStream = new CryptoStream(sourceStream, crypto.CreateDecryptor(),
                        CryptoStreamMode.Read))
                    {
                        deStream.CopyTo(targetStream);
                    }
                }
            }
        }
    }
}
