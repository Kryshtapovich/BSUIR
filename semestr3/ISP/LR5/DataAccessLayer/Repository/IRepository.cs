using Models;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace DataAccessLayer
{
    public interface IRepository
    {
        IEnumerable<Person> ReadPersons(StoredProcedure procedure);

        Task<IEnumerable<Person>> ReadPersonsAsync(StoredProcedure procedure);

        void WriteError(StoredProcedure procedure);

        Task WriteErrorAsync(StoredProcedure procedure);
    }
}
