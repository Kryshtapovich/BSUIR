using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace LR2
{
    static class Encryptor
    {

        private static DESCryptoServiceProvider Crypto { get; set; } = new DESCryptoServiceProvider();

        public static void GetCryptoOptions(string key, string vector)
        {
            Crypto.Key = Encoding.ASCII.GetBytes(key);
            Crypto.IV = Encoding.ASCII.GetBytes(vector);
        }

        public static void Encrypt(Stream sourceStream, Stream targetEncryptedStream)
        {
            using (var ecStream = new CryptoStream(targetEncryptedStream, Crypto.CreateEncryptor(), CryptoStreamMode.Write))
            {
                sourceStream.CopyTo(ecStream);
            }
        }

        public static void Decrypt(Stream sourceEncryptedStream, Stream targetDecryptedStream)
        {
            using (var dcStream = new CryptoStream(sourceEncryptedStream, Crypto.CreateDecryptor(), CryptoStreamMode.Read))
            {
                dcStream.CopyTo(targetDecryptedStream);
            }
        }

        public static string TargetEncryptedFilePath(string fileName, string targetDir)
        {
            fileName = fileName.Replace(Path.GetDirectoryName(fileName), targetDir);
            return fileName.Replace(Path.GetFileName(fileName), Path.GetFileNameWithoutExtension(fileName) + "_encrypted" + Path.GetExtension(fileName));
        }

        public static string TargetDecryptedFilePath(string fileName, string targetDir)
        {
            fileName = Path.Combine(targetDir, fileName);
            string name = Path.GetFileNameWithoutExtension(fileName);
            name = name.Replace("_encrypted", "_decrypted");
            return fileName.Replace(Path.GetFileNameWithoutExtension(fileName), name);
        }
    }
}
