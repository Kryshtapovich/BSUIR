using DbmsProject.Contexts;
using DbmsProject.Models;
using DbmsProject.Windows;
using System.ComponentModel;
using System.Windows;

namespace DbmsProject
{
    public partial class UserWindow : Window
    {

        private readonly ApplicationContext context;

        public UserWindow(ApplicationContext context)
        {
            InitializeComponent();
            this.context = context;
            FisrtName.Text = context.User.FirstName;
            LastName.Text = context.User.LastName;
            Email.Text = context.User.Email;
            ProductsGrid.ItemsSource = context.GetProducts();
            context.GetCategories().ForEach(x => Categories.Items.Add(x.Name));
        }

        private void CreateOrder_Click(object sender, RoutedEventArgs e)
        {
            var product = (Product)ProductsGrid.SelectedItem;
            var selectionWindow = new StoreSelectionWindow(context, product);
            selectionWindow.Show();
        }

        private void GetOrders_Click(object sender, RoutedEventArgs e)
        {
            OrdersGrid.ItemsSource = context.GetOrders();
        }

        private void ProductInfo_Click(object sender, RoutedEventArgs e)
        {
            var product = (Product)ProductsGrid.SelectedItem;
            var productInfoWindow = new ProductInfoWindow(product, context);
            productInfoWindow.Show();
        }

        private void Update_Click(object sender, RoutedEventArgs e)
        {
            context.UpdateUserInfo(FisrtName.Text, LastName.Text, Email.Text, Password.Text);
        }

        private void Sort_Click(object sender, RoutedEventArgs e)
        {
            var category = Categories.SelectedItem;
            ProductsGrid.ItemsSource = context.GetFilteredProducts((string)category);
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            new MainWindow().Show();
        }
    }
}
