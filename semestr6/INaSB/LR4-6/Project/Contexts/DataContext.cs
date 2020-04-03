using DbmsProject.Extensions;
using DbmsProject.Models;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;

namespace DbmsProject.Data
{
    delegate void Logger(string info);

    class DataContext
    {
        private readonly string connectionString =
            "Data Source=LAPTOP-QT7D1CCM;Initial Catalog=DbmsProject;Integrated Security=True";

        private readonly SqlConnection connection;

        private event Logger Log;

        public DataContext()
        {
            connection = new SqlConnection(connectionString);
            Log += AddLog;
        }

        private List<T> ReadProcedure<T>(string procedureName, Dictionary<string, object> parameters) where T : new()
        {
            connection.Open();
            var command = new SqlCommand();
            command.SetParameters(connection, procedureName, parameters);
            var result = command.Read<T>();
            connection.Close();
            return result;
        }

        private void WriteProcedure(string procedureName, Dictionary<string, object> parameters)
        {
            connection.Open();
            var command = new SqlCommand();
            command.SetParameters(connection, procedureName, parameters);
            command.ExecuteNonQuery();
            connection.Close();
        }

        public Account GetAccount(string email, string passwordHash)
        {
            var result = ReadProcedure<Account>("GetAccount", new Dictionary<string, object>
            {
                { "@Email", email },
                { "@PasswordHash", passwordHash }
            });
            return result.FirstOrDefault();
        }

        public void AddAccount(Account user, string passwordHash)
        {
            WriteProcedure("AddAccount", new Dictionary<string, object>
            {
                { "@FirstName", user.FirstName },
                { "@LastName", user.LastName },
                { "@Email", user.Email },
                { "@PasswordHash", passwordHash }
            });
            Log($"User firstname: {user.FirstName} email: {user.Email} registered");
        }

        public void UpdateAccount(Account account)
        {
            WriteProcedure("UpdateAccount", new Dictionary<string, object>
            {
                { "@AccountId", account.Id },
                { "@FirstName", account.FirstName },
                { "@LastName", account.LastName },
                { "@Email", account.Email },
                { "@PasswordHash", account.PasswordHash }
            });
            Log($"Account id: {account.Id} updated");
        }

        public List<Product> GetProducts() => ReadProcedure<Product>("GetProducts", null);

        public List<Product> GetFilteredProducts(string category)
        {
            return ReadProcedure<Product>("GetProductsByCategory", new Dictionary<string, object>
            {
                { "@CategoryName", category}
            });
        }

        public List<Image> GetProductImages(Product product)
        {
            return ReadProcedure<Image>("GetProductImages", new Dictionary<string, object>
            {
                { "@ProductId", product.Id }
            });
        }

        public List<Store> GetProductStores(Product product)
        {
            return ReadProcedure<Store>("GetProductStores", new Dictionary<string, object>
            {
                { "@ProductId", product.Id }
            });
        }

        public List<Category> GetCategories() => ReadProcedure<Category>("GetCategories", null);

        public List<Order> GetAccountOrders(Account account)
        {
            return ReadProcedure<Order>("GetAccountOrders", new Dictionary<string, object>
            {
                { "@AccountId", account.Id }
            });
        }

        public void CreateOrder(Account account, Product product, Store store)
        {
            WriteProcedure("AddOrder", new Dictionary<string, object>
            {
                { "@AccountId", account.Id },
                { "@ProductId", product.Id },
                { "@StoreId", store.Id },
                { "@Date", DateTime.Now }
            });
            Log($"User id: {account.Id} bought Product id: {product.Id} from Store id: {store.Id}");
        }

        public void AddCategory(string categoryName)
        {
            WriteProcedure("AddCategory", new Dictionary<string, object>
            {
                { "@Name", categoryName}
            });
            Log($"Category: {categoryName} added");
        }

        public void UpdateCategory(Category category)
        {
            WriteProcedure("UpdateCategory", new Dictionary<string, object>
            {
                { "@CategoryId", category.Id },
                { "@CategoryName", category.Name }
            });
            Log($"Category: {category.Name} updated");
        }

        public void AddProduct(Product product, string store)
        {
            WriteProcedure("AddProduct", new Dictionary<string, object>
            {
                { "@CategoryName", product.CategoryName },
                { "@StoreName", store },
                { "@Name", product.Name },
                { "@Description", product.Description },
                { "@Price", product.Price }
            });
            Log($"Product name: {product.Name} store: {store} category: {product.CategoryName} added");
        }

        public void UpdateProduct(Product product)
        {
            WriteProcedure("UpdateProduct", new Dictionary<string, object>
            {
                { "@ProductId", product.Id },
                { "@ProductName", product.Name },
                { "@ProductDescription", product.Description },
                { "@ProductPrice", product.Price }
            });
            Log($"Product id: {product.Id} updated");
        }

        public void DeleteProduct(Product product)
        {
            WriteProcedure("DeleteProduct", new Dictionary<string, object> { { "@ProductId", product.Id } });
            Log($"Product id: {product.Id} deleted");
        }

        public List<Store> GetStores() => ReadProcedure<Store>("GetStores", null);

        public void AddStore(Store store)
        {
            WriteProcedure("AddStore", new Dictionary<string, object>
            {
                { "@Name", store.Name },
                { "@Address", store.Address }
            });
            Log($"Store name: {store.Name} address: {store.Address} added");
        }

        public void UpdateStore(Store store)
        {
            WriteProcedure("UpdateStore", new Dictionary<string, object>
            {
                { "@StoreId", store.Id },
                { "@StoreName", store.Name },
                { "@Address", store.Address }
            });
            Log($"Store id:{store.Id} updated");
        }

        public List<Image> GetImages(Product product)
        {
            return ReadProcedure<Image>("GetProductImages", new Dictionary<string, object>
            {
                { "@ProductId", product.Id }
            });
        }

        public void AddImage(Image image)
        {
            WriteProcedure("AddImage", new Dictionary<string, object>
            {
                { "@ProductId", image.ProductId },
                { "@Url", image.Url }
            });
            Log($"Image url: {image.Url} added to Product id: {image.ProductId}");
        }

        public void DeleteImage(Image image)
        {
            WriteProcedure("DeleteImage", new Dictionary<string, object>
            {
                { "@ImageId", image.Id }
            });
            Log($"Image id: {image.Id} deleted");
        }

        public List<Log> GetLogs() => ReadProcedure<Log>("GetLogs", null);

        public void AddLog(string info)
        {
            WriteProcedure("AddLog", new Dictionary<string, object>
            {
                { "@Info", info },
                { "@Date", DateTime.Now }
            });
        }
    }
}
