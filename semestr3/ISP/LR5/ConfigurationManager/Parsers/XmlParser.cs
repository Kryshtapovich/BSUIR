using System.IO;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace ConfigurationManager
{
    class XmlParser : IParser
    {
        private readonly string xmlPath;

        public XmlParser(string xmlPath)
        {
            this.xmlPath = xmlPath;
        }

        public T Parse<T>() where T : new()
        {
            T obj = new T();

            XmlSerializer serializer = new XmlSerializer(typeof(T));
            using (var fs = new FileStream(xmlPath, FileMode.OpenOrCreate))
            {
                obj = (T)serializer.Deserialize(fs);
            }

            return obj;
        }

        public async Task<T> ParseAsync<T>() where T : new()
        {
            return await Task.Run(() => Parse<T>());
        }
    }
}
