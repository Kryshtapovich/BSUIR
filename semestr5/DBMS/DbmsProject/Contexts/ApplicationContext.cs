using DbmsProject.Data;
using DbmsProject.Models;
using DbmsProject.Services;
using System;
using System.Collections.Generic;

namespace DbmsProject.Contexts
{
    public class ApplicationContext
    {
        public Account User { get; private set; }

        private readonly DataContext data;

        public ApplicationContext()
        {
            data = new DataContext();
        }

        public void Authorize(string email, string password)
        {
            var hasher = new Hasher();
            var passwordHash = hasher.GetHash(password);
            var account = data.GetAccount(email, passwordHash);
            User = account is null ? throw new NullReferenceException("User doesn't exist") : account;
        }

        public void Register(Account user, string password)
        {
            var hasher = new Hasher();
            var passwordHash = hasher.GetHash(password);
            data.AddAccount(user, passwordHash);
            User = data.GetAccount(user.Email, passwordHash);
        }

        public void UpdateUserInfo(string fisrtName, string lastName, string email, string password)
        {
            if (fisrtName.Length != 0 && fisrtName != User.FirstName)
                User.FirstName = fisrtName;
            if (lastName.Length != 0 && lastName != User.LastName)
                User.LastName = lastName;
            if (email.Length != 0 && email != User.Email)
                User.Email = email;
            if (password.Length != 0)
                User.PasswordHash = new Hasher().GetHash(password);

            data.UpdateAccount(User);
        }

        public List<Product> GetProducts() => data.GetProducts();

        public List<Product> GetFilteredProducts(string category) => data.GetFilteredProducts(category);

        public List<Image> GetProductImages(Product product) => data.GetProductImages(product);

        public List<Store> GetProductStores(Product product) => data.GetProductStores(product);

        public List<Order> GetOrders() => data.GetAccountOrders(User);

        public List<Category> GetCategories() => data.GetCategories();

        public void Buy(Product product, Store store) => data.CreateOrder(User, product, store);

        public void AddCategory(string categoryName) => data.AddCategory(categoryName);

        public void UpdateCategory(Category category) => data.UpdateCategory(category);

        public void AddProduct(Product product, string store) => data.AddProduct(product, store);

        public void UpdateProduct(Product product) => data.UpdateProduct(product);

        public void DeleteProduct(Product product) => data.DeleteProduct(product);

        public List<Store> GetStores() => data.GetStores();

        public void AddStore(Store store) => data.AddStore(store);

        public void UpdateStore(Store store) => data.UpdateStore(store);

        public List<Image> GetImages(Product product) => data.GetImages(product);

        public void AddImage(Image image) => data.AddImage(image);

        public void DeleteImage(Image image) => data.DeleteImage(image);

        public List<Log> GetLogs() => data.GetLogs();
    }
}
