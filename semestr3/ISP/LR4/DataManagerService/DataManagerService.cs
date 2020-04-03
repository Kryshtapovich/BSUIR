using ConfigurationManager;
using FileManager;
using Models;
using ServiceLayer;
using System;
using System.ServiceProcess;

namespace DataManagerService
{
    public partial class DataManagerService : ServiceBase
    {
        private DataManagerOptions dataManagerOptions;

        private Database personDb;

        private Database errorDb;

        public DataManagerService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            try
            {
                OptionsManager manager = new OptionsManager(@"E:\LR4\DataManagerService\bin\Release\AppSettings.xml");
                dataManagerOptions = manager.GetOptions<DataManagerOptions>();

                errorDb = new Database(dataManagerOptions.ErrorConnectionString);
                personDb = new Database(dataManagerOptions.ConnectionString);
                var persons = personDb.GetPersons(dataManagerOptions.SearchCriteria);

                XmlXsdGenerator<Person> generator = new XmlXsdGenerator<Person>(persons);
                var xmlString = generator.GenerateXml();
                var xsdString = generator.GenerateXsd();

                FileManagerService fileManager = new FileManagerService();
                fileManager.Launch();

                FileSender sender = new FileSender(dataManagerOptions.FtpSourceFolder);
                sender.Send(xmlString, xsdString);
            }
            catch (Exception ex)
            {
                Error error = new Error(ex.Source, ex.Message, ex.StackTrace, DateTime.Now);
                errorDb.LogError(error);
            }

        }

        public void OnDebug()
        {
            OnStart(null);
        }

        protected override void OnStop()
        {

        }
    }
}
