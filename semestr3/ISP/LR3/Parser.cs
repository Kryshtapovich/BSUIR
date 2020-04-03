using System.IO;

namespace LR2
{
    public class Parser
    {
        private readonly IParser parser;

        public Parser(string path)
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

        public T Parse<T>() where T : new()
        {   
            try
            {
                return parser.Parse<T>();
            }
            catch(Exception ex)
            {
                throw ex;   
            }
        }
    }
}
