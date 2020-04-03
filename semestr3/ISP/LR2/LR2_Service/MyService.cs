using System;
using System.IO;
using System.ServiceProcess;
using System.Threading;

namespace LR2
{
    public partial class MyService : ServiceBase
    {
        private Logger logger;

        public MyService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            try
            {
                logger = new Logger();
                Thread loggerThread = new Thread(new ThreadStart(logger.Start));
                loggerThread.Start();
            }
            catch (Exception e)
            {
                using (var errorStream = new StreamWriter(new FileStream(Archivator.errorFile, FileMode.OpenOrCreate)))
                {
                    errorStream.Write(e.Message);
                }
            }
        }

        public void OnDebug()
        {
            OnStart(null);
        }

        protected override void OnStop()
        {
            logger.Stop();
            Thread.Sleep(1000);
        }
    }
}
