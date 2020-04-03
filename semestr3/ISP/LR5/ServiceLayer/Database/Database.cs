using DataAccessLayer;
using Models;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace ServiceLayer
{
    public class Database
    {
        private readonly IRepository repo;

        public Database(string connectionString)
        {
            repo = new Repository(connectionString);
        }

        public async Task<IEnumerable<Person>> GetPersonsAsync(SearchCriteria criteria)
        {
            string procedureName = "GetPersons";
            Dictionary<string, object> parameters = new Dictionary<string, object>
            {
                {"@Amount", criteria.Amount},
                {"@SortParameter", criteria.SortParameter},
                {"@OrderBy", criteria.Order}
            };

            return await repo.ReadPersonsAsync(new StoredProcedure(procedureName, parameters));
        }

        public async Task LogErrorAsync(Error error)
        {
            string procedureName = "AddError";
            Dictionary<string, object> parameters = new Dictionary<string, object>
            {
                {"@Source", error.Source},
                {"@Message", error.Message},
                {"@StackTrace", error.StackTrace},
                {"@Time", error.Time},
            };

            await repo.WriteErrorAsync(new StoredProcedure(procedureName, parameters));
        }
    }
}
