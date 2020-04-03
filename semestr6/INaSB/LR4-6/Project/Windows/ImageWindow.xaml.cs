using DbmsProject.Contexts;
using DbmsProject.Models;
using System.Windows;

namespace DbmsProject.Windows
{
    public partial class ImageWindow : Window
    {
        private readonly ApplicationContext context;

        private readonly Product product;

        public ImageWindow(ApplicationContext context, Product product)
        {
            this.context = context;
            this.product = product;
            InitializeComponent();
        }

        private void GetImages_Click(object sender, RoutedEventArgs e)
        {
            Images.ItemsSource = context.GetImages(product);
        }

        private void AddImage_Click(object sender, RoutedEventArgs e)
        {
            var image = new Image
            {
                Url = ImageUrl.Text,
                ProductId = product.Id
            };
            context.AddImage(image);
        }

        private void DeleteImage_Click(object sender, RoutedEventArgs e)
        {
            var image = (Image)Images.SelectedItem;
            context.DeleteImage(image);
        }
    }
}
