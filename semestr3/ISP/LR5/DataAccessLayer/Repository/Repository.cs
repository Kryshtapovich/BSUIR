using Models;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Threading.Tasks;

namespace DataAccessLayer
{
    public class Repository : IRepository
    {
        private readonly SqlConnection sqlConnection;

        public Repository(string connectionString)
        {
            sqlConnection = new SqlConnection(connectionString);
        }

        public IEnumerable<Person> ReadPersons(StoredProcedure procedure)
        {
            IEnumerable<Person> people;

            sqlConnection.Open();
            var transaction = sqlConnection.BeginTransaction();

            try
            {
                SqlCommand command = new SqlCommand();
                command.SetParameters(procedure, sqlConnection, transaction);

                people = command.Read<Person>();

                transaction.Commit();
            }
            catch (Exception ex)
            {
                transaction.Rollback();
                throw ex;
            }
            finally
            {
                sqlConnection.Close();
            }

            return people;
        }

        public async Task<IEnumerable<Person>> ReadPersonsAsync(StoredProcedure procedure)
        {
            return await Task.Run(() => ReadPersons(procedure));
        }

        public void WriteError(StoredProcedure procedure)
        {
            sqlConnection.Open();
            var transaction = sqlConnection.BeginTransaction();

            try
            {
                SqlCommand command = new SqlCommand();
                command.SetParameters(procedure, sqlConnection, transaction);
                command.ExecuteNonQuery();

                transaction.Commit();
            }
            catch (Exception ex)
            {
                transaction.Rollback();
                throw ex;
            }
            finally
            {
                sqlConnection.Close();
            }
        }

        public async Task WriteErrorAsync(StoredProcedure procedure)
        {
            await Task.Run(() => WriteError(procedure));
        }
    }
}
