using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;

namespace WEB_953506_Kryshtapovich.Middleware
{
    public class LogMiddleware
    {
        private RequestDelegate next;
        private ILogger<LogMiddleware> logger;

        public LogMiddleware(RequestDelegate next, ILogger<LogMiddleware> logger)
        {
            this.next = next;
            this.logger = logger;
        }

        public async Task Invoke(HttpContext context)
        {
            await next.Invoke(context);
            if(context.Response.StatusCode!=StatusCodes.Status200OK)
            {
                var path = context.Request.Path + context.Request.QueryString;
                logger.LogInformation($"Request {path} returns status code {context.Response.StatusCode}");
            }
        }
    }
}