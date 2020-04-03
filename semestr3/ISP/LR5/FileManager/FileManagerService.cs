using ConfigurationManager;
using Models;
using System.ServiceProcess;
using System.Threading;
using System.Threading.Tasks;

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

        protected override void OnStart(string[] args) { }

        private async Task StartAsync()
        {
            OptionsManager optionsManager = new OptionsManager(@"E:\LR5\FileManager\bin\Release\AppSettings.json");
            options = await optionsManager.GetOptionsAsync<FileManagerOptions>();
            logger = new Logger(options);
            Thread loggerThread = new Thread(new ThreadStart(logger.Start));
            loggerThread.Start();
        }

        protected override void OnStop()
        {
            logger.Stop();
            Thread.Sleep(1000);
        }

        public async Task LaunchAsync()
        {
            await StartAsync();
        }
    }
}
