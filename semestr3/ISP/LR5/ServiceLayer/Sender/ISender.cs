using System.Threading.Tasks;

namespace ServiceLayer
{
    interface ISender
    {
        Task SendAsync(string xmlContent, string xsdContent);
    }
}
