using DbmsProject.Contexts;
using DbmsProject.Models;
using System.Windows;

namespace DbmsProject.Windows
{
    /// <summary>
    /// Interaction logic for StoreChoose.xaml
    /// </summary>
    public partial class StoreSelectionWindow : Window
    {
        private ApplicationContext context;

        private Product selectedProduct;

        public StoreSelectionWindow(ApplicationContext context, Product product)
        {
            this.context = context;
            selectedProduct = product;
            InitializeComponent();
        }

        private void Buy_Click(object sender, RoutedEventArgs e)
        {
            var selectedStore = (Store)Stores.SelectedItem;
            context.Buy(selectedProduct, selectedStore);
        }

        private void GetStores_Click(object sender, RoutedEventArgs e)
        {
            Stores.ItemsSource = context.GetProductStores(selectedProduct);
        }
    }
}
