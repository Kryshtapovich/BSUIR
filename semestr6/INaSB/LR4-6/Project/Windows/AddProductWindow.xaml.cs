using DbmsProject.Contexts;
using DbmsProject.Models;
using System.Collections.Generic;
using System.Windows;

namespace DbmsProject.Windows
{
    public partial class AddProductWindow : Window
    {
        private readonly ApplicationContext context;

        private readonly List<Category> categories;

        private readonly List<Store> stores;

        public AddProductWindow(ApplicationContext context)
        {
            this.context = context;
            InitializeComponent();
            categories = context.GetCategories();
            stores = context.GetStores();
            categories.ForEach(x => Category.Items.Add(x.Name));
            stores.ForEach(x => Store.Items.Add(x.Name));
        }

        private void Add_Click(object sender, RoutedEventArgs e)
        {
            var product = new Product
            {
                Name = Name.Text,
                Price = decimal.Parse(Price.Text),
                CategoryName = (string)Category.SelectedItem,
                Description = Description.Text
            };
            var store = (string)Store.SelectedItem;
            context.AddProduct(product, store);
        }
    }
}
