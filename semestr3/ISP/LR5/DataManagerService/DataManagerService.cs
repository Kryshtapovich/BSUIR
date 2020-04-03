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

        protected override async void OnStart(string[] args)
        {
            try
            {
                OptionsManager manager = new OptionsManager(@"E:\LR5\DataManagerService\bin\Release\AppSettings.xml");
                dataManagerOptions = await manager.GetOptionsAsync<DataManagerOptions>();

                errorDb = new Database(dataManagerOptions.ErrorConnectionString);
                personDb = new Database(dataManagerOptions.ConnectionString);
                var persons = await personDb.GetPersonsAsync(dataManagerOptions.SearchCriteria);

                XmlXsdGenerator<Person> generator = new XmlXsdGenerator<Person>(persons);
                var xmlString = generator.GenerateXml();
                var xsdString = generator.GenerateXsd();

                FileManagerService filemanager = new FileManagerService();
                await filemanager.LaunchAsync();

                FileSender sender = new FileSender(dataManagerOptions.FtpSourceFolder);
                await sender.SendAsync(xmlString, xsdString);
            }
            catch (Exception e)
            {
                await errorDb.LogErrorAsync(new Error(e.Message, e.Source, e.StackTrace, DateTime.Now));
            }

        }

        public void OnDebug()
        {
            OnStart(null);
        }

        protected override void OnStop() { }
    }
}