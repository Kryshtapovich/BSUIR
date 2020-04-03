using System;
using System.Collections.Generic;
using System.Data.SqlClient;

namespace DbmsProject.Extensions
{
    static class SqlCommandExtension
    {
        public static List<T> Read<T>(this SqlCommand command) where T : new()
        {
            using (var reader = command.ExecuteReader())
            {
                var entities = new List<T>();

                if (!reader.HasRows)
                {
                    return entities;
                }

                var properties = typeof(T).GetProperties();

                while (reader.Read())
                {
                    var obj = new T();

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

        public static void SetParameters(this SqlCommand command, SqlConnection connection,
            string procedureName, Dictionary<string, object> parameters)
        {
            command.CommandText = procedureName;
            command.CommandType = System.Data.CommandType.StoredProcedure;
            command.Connection = connection;
            if (parameters is not null)
            {
                foreach (var item in parameters)
                {
                    command.Parameters.AddWithValue(item.Key, item.Value);
                }
            }
        }
    }
}
