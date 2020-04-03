using System;
using System.IO;
using System.Linq;

namespace ConfigurationManager
{
    public class OptionsManager
    {
        private IParser parser;

        public OptionsManager()
        {
            var s = Directory.GetCurrentDirectory();

            var files = Directory.GetFiles(Directory.GetCurrentDirectory(), "AppSettings.*");

            string configFile = files.Length > 1 ? files.Single(x => Path.GetExtension(x) == ".xml") : files[0];

            ChooseParser(configFile);
        }

        public OptionsManager(string path)
        {
            ChooseParser(path);
        }

        private void ChooseParser(string path)
        {
            if (Path.GetExtension(path) == ".xml")
            {
                parser = new XmlParser(path);
            }
            else if (Path.GetExtension(path) == ".json")
            {
                parser = new JsonParser(path);
            }
        }

        public T GetOptions<T>() where T : new()
        {
            try
            {
                return parser.Parse<T>();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
}
