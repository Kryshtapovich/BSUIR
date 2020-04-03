using System.IO;
using System.Text.Json;
using System.Threading.Tasks;

namespace ConfigurationManager
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

            string jsonString = File.ReadAllText(jsonPath);
            obj = JsonSerializer.Deserialize<T>(jsonString);

            return obj;
        }

        public async Task<T> ParseAsync<T>() where T : new()
        {
            return await Task.Run(() => Parse<T>());
        }
    }
}
