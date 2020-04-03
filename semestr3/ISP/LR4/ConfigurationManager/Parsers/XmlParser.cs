using System;
using System.IO;
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

            try
            {
                XmlSerializer serializer = new XmlSerializer(typeof(T));
                using (var fs = new FileStream(xmlPath, FileMode.OpenOrCreate))
                {
                    obj = (T)serializer.Deserialize(fs);
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }

            return obj;
        }
    }
}
