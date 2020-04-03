using System.ServiceProcess;
using System.Threading;
namespace LR2
{
    static class Program
    {
        static void Main()
        {
#if DEBUG
            MyService myService = new MyService();
            myService.OnDebug();
            Thread.Sleep(Timeout.Infinite);
#else
            ServiceBase[] ServicesToRun;
            ServicesToRun = new ServiceBase[]
            {
                new MyService()
            };
            ServiceBase.Run(ServicesToRun);
#endif
        }
    }
}
