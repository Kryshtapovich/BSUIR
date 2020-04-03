using System.Collections.Generic;

namespace DataAccessLayer
{
    public class StoredProcedure
    {
        public string Name { get; set; }

        public Dictionary<string, object> Parameters { get; set; }

        public StoredProcedure(string name, Dictionary<string, object> parameters)
        {
            Name = name;
            Parameters = parameters;
        }
    }
}
