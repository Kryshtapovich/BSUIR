using ConfigurationManager;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading;
using Models;
using System.Threading.Tasks;
using System.IO;

namespace FileManager
{
    public partial class FileManagerService : ServiceBase
    {
        private Logger logger;

        private FileManagerOptions options;

        public FileManagerService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            try
            {
                OptionsManager optionsManager = new OptionsManager(@"E:\LR4\FileManager\bin\Release\AppSettings.json");
                options = optionsManager.GetOptions<FileManagerOptions>();
                logger = new Logger(options);
                Thread loggerThread = new Thread(new ThreadStart(logger.Start));
                loggerThread.Start();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        protected override void OnStop()
        {
            logger.Stop();
            Thread.Sleep(1000);
        }

        public void Launch()
        {
            try
            {
                OnStart(null);
            }catch(Exception ex)
            {
                throw ex;
            }
        }
    }
}
