using Models;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;

namespace DataAccessLayer
{
    public class Repository : IRepository
    {
        private readonly SqlConnection sqlConnection;

        public Repository(string connectionString)
        {
            sqlConnection = new SqlConnection(connectionString);
        }

        private void OpenConnection()
        {
            try
            {
                sqlConnection.Open();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void CloseConnection()
        {
            try
            {
                sqlConnection.Close();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        IEnumerable<Person> IRepository.ReadPersons(StoredProcedure procedure)
        {
            IEnumerable<Person> people;

            OpenConnection();
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
                CloseConnection();
            }

            return people;
        }

        void IRepository.WriteError(StoredProcedure procedure)
        {
            OpenConnection();
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
                CloseConnection();
            }
        }
    }
}
