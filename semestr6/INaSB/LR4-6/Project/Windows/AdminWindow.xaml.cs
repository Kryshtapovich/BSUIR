using DbmsProject.Contexts;
using DbmsProject.Models;
using DbmsProject.Windows;
using System.ComponentModel;
using System.Windows;

namespace DbmsProject
{
    public partial class AdminWindow : Window
    {
        private readonly ApplicationContext context;

        public AdminWindow(ApplicationContext context)
        {
            InitializeComponent();
            this.context = context;
        }

        private void GetCategories_Click(object sender, RoutedEventArgs e)
        {
            Categories.ItemsSource = context.GetCategories();
        }

        private void UpdateCategory_Click(object sender, RoutedEventArgs e)
        {
            var category = (Category)Categories.SelectedItem;
            context.UpdateCategory(category);
        }

        private void AddCategory_Click(object sender, RoutedEventArgs e)
        {
            context.AddCategory(CategoryName.Text);
        }

        private void GetProducts_Click(object sender, RoutedEventArgs e)
        {
            Products.ItemsSource = context.GetProducts();
        }

        private void AddProduct_Click(object sender, RoutedEventArgs e)
        {
            var addProductWindow = new AddProductWindow(context);
            addProductWindow.Show();
        }

        private void UpdateProduct_Click(object sender, RoutedEventArgs e)
        {
            var product = (Product)Products.SelectedItem;
            context.UpdateProduct(product);
        }

        private void DeleteProduct_Click(object sender, RoutedEventArgs e)
        {
            var product = (Product)Products.SelectedItem;
            context.DeleteProduct(product);
        }

        private void GetStores_Click(object sender, RoutedEventArgs e)
        {
            Stores.ItemsSource = context.GetStores();
        }

        private void UpdateStore_Click(object sender, RoutedEventArgs e)
        {
            var store = (Store)Stores.SelectedItem;
            context.UpdateStore(store);
        }

        private void AddStore_Click(object sender, RoutedEventArgs e)
        {
            var store = new Store
            {
                Name = StoreName.Text,
                Address = Address.Text
            };
            context.AddStore(store);
        }

        private void Image_Click(object sender, RoutedEventArgs e)
        {
            var product = (Product)Products.SelectedItem;
            var imageWindow = new ImageWindow(context, product);
            imageWindow.Show();
        }

        private void GetLogs_Click(object sender, RoutedEventArgs e)
        {
            Logs.ItemsSource = context.GetLogs();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            new MainWindow().Show();
        }
    }
}
