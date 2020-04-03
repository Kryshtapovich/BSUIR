using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;

namespace DataAccessLayer
{
    static class SqlCommandExtension
    {
        public static IEnumerable<T> Read<T>(this SqlCommand command) where T : new()
        {
            return ReadByProcedure<T>(command);
        }

        private static IEnumerable<T> ReadByProcedure<T>(SqlCommand command) where T : new()
        {
            using (var reader = command.ExecuteReader())
            {
                if (!reader.HasRows)
                {
                    return Enumerable.Empty<T>();
                }

                var entities = new List<T>();

                var properties = typeof(T).GetProperties();

                while (reader.Read())
                {
                    T obj = new T();

                    foreach (var property in properties)
                    {
                        var readerValue = reader[property.Name] is DBNull ? null : reader[property.Name];

                        property.SetValue(obj, readerValue);
                    }

                    entities.Add(obj);
                }

                return entities;
            }
        }

        public static void SetParameters(this SqlCommand command, StoredProcedure procedure,
            SqlConnection connection, SqlTransaction transaction)
        {
            command.CommandText = procedure.Name;
            command.CommandType = CommandType.StoredProcedure;
            command.Connection = connection;
            command.Transaction = transaction;
            foreach (var parameter in procedure.Parameters)
            {
                command.Parameters.AddWithValue(parameter.Key, parameter.Value);
            }
        }
    }
}
