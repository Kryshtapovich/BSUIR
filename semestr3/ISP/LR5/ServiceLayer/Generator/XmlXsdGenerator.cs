using System.Collections.Generic;
using System.IO;
using System.Xml;
using System.Xml.Linq;
using System.Xml.Schema;

namespace ServiceLayer
{
    public class XmlXsdGenerator<T> : IGenerator
    {
        private readonly IEnumerable<T> collection;

        private string xmlString;

        private string xsdString;

        public XmlXsdGenerator(IEnumerable<T> collection)
        {
            this.collection = collection;
        }

        public string GenerateXsd()
        {
            XmlReader reader = XmlReader.Create(new StringReader(xmlString));
            XmlSchemaSet schemaSet = new XmlSchemaSet();
            XmlSchemaInference schema = new XmlSchemaInference();
            schemaSet = schema.InferSchema(reader);

            foreach (XmlSchema s in schemaSet.Schemas())
            {
                using (var stringWriter = new StringWriter())
                {
                    XmlWriterSettings settings = new XmlWriterSettings { Indent = true };

                    using (var writer = XmlWriter.Create(stringWriter, settings))
                    {
                        s.Write(writer);
                        xsdString = stringWriter.ToString();
                    }
                }
            }

            return xsdString;
        }

        private XElement ObjectToXml<T>(T obj)
        {
            XElement root = new XElement(typeof(T).Name);
            var properties = typeof(T).GetProperties();

            foreach (var property in properties)
            {
                XElement element = new XElement(property.Name, property.GetValue(obj));
                root.Add(element);
            }

            return root;
        }

        public string GenerateXml()
        {
            XElement persons = new XElement("Persons");

            foreach (var item in collection)
            {
                persons.Add(ObjectToXml(item));
            }

            xmlString = new XDeclaration("1.0", "utf-16", "yes").ToString() + "\n" + persons.ToString();

            return xmlString;
        }
    }
}
