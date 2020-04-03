using System.Threading;
using System.ServiceProcess;

namespace DataManagerService
{
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        static void Main()
        {
#if DEBUG
            DataManagerService service = new DataManagerService();
            service.OnDebug();
            Thread.Sleep(Timeout.Infinite);
#else
            ServiceBase[] ServicesToRun;
            ServicesToRun = new ServiceBase[]
            {
                new DataManagerService()
            };
            ServiceBase.Run(ServicesToRun);
#endif
        }
    }
}
