using System.ServiceProcess;
using System.Threading;

namespace FileManager
{
    static class Program
    {
        static void Main()
        {
#if DEBUG
            FileManagerService service = new FileManagerService();
            service.Launch();
            Thread.Sleep(Timeout.Infinite);
#else
            ServiceBase[] ServicesToRun;
            ServicesToRun = new ServiceBase[]
            {
                new FileManagerService()
            };
            ServiceBase.Run(ServicesToRun);
#endif
        }
    }
}
