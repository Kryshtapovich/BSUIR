using System;
using System.IO;
using System.Text.Json;

namespace LR2
{
    class JsonParser : IParser
    {
        private readonly string jsonPath;

        public JsonParser(string jsonPath)
        {
            this.jsonPath = jsonPath;
        }

        public T Parse<T>() where T : new()
        {
            T obj = new T();

            try
            {
                string jsonString = File.ReadAllText(jsonPath);
                obj = JsonSerializer.Deserialize<T>(jsonString);
            }
            catch (Exception ex)
            {
                throw ex;
            }

            return obj;
        }
    }
}
