using System.Threading.Tasks;

namespace ConfigurationManager
{
    interface IParser
    {
        Task<T> ParseAsync<T>() where T : new();

        T Parse<T>() where T : new();
    }
}
