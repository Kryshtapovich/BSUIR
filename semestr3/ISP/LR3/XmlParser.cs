using System;
using System.IO;
using System.Xml.Linq;
using System.Xml.Schema;
using System.Xml.Serialization;

namespace LR2
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
                Validate();
                XmlSerializer serializer = new XmlSerializer(typeof(T));
                using (var fs = new FileStream(xmlPath, FileMode.OpenOrCreate))
                {
                    obj = (T)serializer.Deserialize(fs);
                }
            }
            catch(Exception ex)
            {
                throw ex;
            }

            return obj;
        }

        private void Validate()
        {
            XmlSchemaSet schemas = new XmlSchemaSet();
            var validationPath = Path.Combine(Directory.GetCurrentDirectory(), "Validation.xsd");
            schemas.Add(null, validationPath);

            XDocument document = XDocument.Load(xmlPath);

            document.Validate(schemas, (sender, validationEventArgs) =>
            {
                throw validationEventArgs.Exception;
            });
        }
    }
}
