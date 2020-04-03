using System;
using System.IO;
using System.ServiceProcess;
using System.Threading;

namespace LR2
{
    public partial class MyService : ServiceBase
    {
        private Logger logger;

        private ConfigurationOptions options;

        private readonly string errorFile = "Error.txt";

        public MyService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            try
            {
                Parser parser = new Parser("Options.xml");
                options = parser.Parse<ConfigurationOptions>();
                logger = new Logger(options, errorFile);
                Thread loggerThread = new Thread(new ThreadStart(logger.Start));
                loggerThread.Start();
            }
            catch (Exception e)
            {
                using (var errorStream = new StreamWriter(new FileStream(errorFile, FileMode.OpenOrCreate)))
                {
                    errorStream.Write(e.Message + "\n" + e.StackTrace);
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
