using System;
using System.IO;
using System.IO.Compression;
using System.Runtime.Serialization.Formatters.Binary;
using System.Xml.Serialization;
using System.Windows;

namespace LR1
{
    static class MyFileClass
    {
        public static void Read(string path, out Student student)
        {
            try
            {
                if (Path.GetExtension(path) == ".bin")
                {
                    using (FileStream fs = new FileStream(path, FileMode.Open))
                    {
                        BinaryFormatter formatter = new BinaryFormatter();
                        student = (Student)formatter.Deserialize(fs);
                    }
                }
                else
                {
                    using (FileStream fs = new FileStream(path, FileMode.Open))
                    {
                        XmlSerializer formatter = new XmlSerializer(typeof(Student));
                        student = (Student)formatter.Deserialize(fs);
                    }
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                student = null;
            }
        }

        public static void Write(string path, Student student)
        {
            try
            {
                if (Path.GetExtension(path) == ".bin")
                {
                    using (FileStream fs = new FileStream(path, FileMode.OpenOrCreate))
                    {
                        BinaryFormatter formatter = new BinaryFormatter();
                        formatter.Serialize(fs, student);
                    }
                }
                else
                {
                    using (FileStream fs = new FileStream(path, FileMode.OpenOrCreate))
                    {
                        XmlSerializer formatter = new XmlSerializer(typeof(Student));
                        formatter.Serialize(fs, student);
                    }
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        public static void Compress(string source, string compressed, out string text)
        {
            try
            {
                using (FileStream sourceStream = new FileStream(source, FileMode.OpenOrCreate))
                {
                    using (FileStream targetStream = File.Create(compressed))
                    {
                        using (GZipStream compressionStream = new GZipStream(targetStream, CompressionMode.Compress))
                        {
                            sourceStream.CopyTo(compressionStream);
                            text = $"Файл сжат\nРазмер до сжатия: {sourceStream.Length}\nРазмер после сжатия: {targetStream.Length}";
                        }
                    }
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                text = "";
            }
        }

        public static void Decompress(string compressed, string recovered, out string text)
        {
            try
            {
                using (FileStream compressedStream = new FileStream(compressed, FileMode.OpenOrCreate))
                {
                    using (FileStream targerStream = File.Create(recovered))
                    {
                        using (GZipStream recoveryStream = new GZipStream(compressedStream, CompressionMode.Decompress))
                        {
                            recoveryStream.CopyTo(targerStream);
                            text = $"Файл восстановлен\nРазмер до восстановления: {compressedStream.Length}\n" +
                                $"Размер после восстановления: {targerStream.Length}";
                        }
                    }
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                text = "";
            }
        }
    }
}
