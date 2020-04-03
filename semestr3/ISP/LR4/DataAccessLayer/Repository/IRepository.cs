using Models;
using System.Collections.Generic;

namespace DataAccessLayer
{
    public interface IRepository
    {
        IEnumerable<Person> ReadPersons(StoredProcedure procedure);

        void WriteError(StoredProcedure procedure);
    }
}
