using Microsoft.AspNetCore.Builder;
using WEB_953506_Kryshtapovich.Middleware;

namespace WEB_953506_Kryshtapovich.Extensions
{
    public static class AppExtensions
    {
        public static IApplicationBuilder UseFileLogging(this IApplicationBuilder app)
        {
            return app.UseMiddleware<LogMiddleware>();
        }
    }
}