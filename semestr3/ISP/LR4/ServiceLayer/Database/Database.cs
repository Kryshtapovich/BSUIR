using DataAccessLayer;
using Models;
using System.Collections.Generic;

namespace ServiceLayer
{
    public class Database
    {
        private readonly IRepository repo;

        public Database(string connectionString)
        {
            repo = new Repository(connectionString);
        }

        public IEnumerable<Person> GetPersons(SearchCriteria criteria)
        {
            string procedureName = "GetPersons";
            Dictionary<string, object> parameters = new Dictionary<string, object>
            {
                {"@Amount", criteria.Amount},
                {"@SortParameter", criteria.SortParameter},
                {"@OrderBy", criteria.Order}
            };

            return repo.ReadPersons(new StoredProcedure(procedureName, parameters));
        }

        public void LogError(Error error)
        {
            string procedureName = "AddError";
            Dictionary<string, object> parameters = new Dictionary<string, object>
            {
                {"@Source", error.Source},
                {"@Message", error.Message},
                {"@StackTrace", error.StackTrace},
                {"@Time", error.Time},
            };
            repo.WriteError(new StoredProcedure(procedureName, parameters));
        }
    }
}
