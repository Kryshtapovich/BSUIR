using System;

namespace Models
{
    [Serializable]
    public class DataManagerOptions
    {
        public string ConnectionString { get; set; }

        public string ErrorConnectionString { get; set; }

        public SearchCriteria SearchCriteria { get; set; }

        public string FtpSourceFolder { get; set; }
    }
}
