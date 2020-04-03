using Microsoft.AspNetCore.Http;

namespace WEB_953506_Kryshtapovich.Extensions
{
    public static class RequestExtension
    {
        public static bool IsAjaxRequest(this HttpRequest request)
        {
            return request.Headers["x-requested-with"].Equals("XMLHttpRequest");
        }
    }
}