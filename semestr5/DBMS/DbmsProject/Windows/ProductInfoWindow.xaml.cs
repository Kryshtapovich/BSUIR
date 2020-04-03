using DbmsProject.Contexts;
using DbmsProject.Models;
using System.Collections.Generic;
using System.Linq;
using System.Windows;

namespace DbmsProject.Windows
{
    public partial class ProductInfoWindow : Window
    {
        private readonly List<Image> productImages;

        private int currentImageIndex;

        public ProductInfoWindow(Product product, ApplicationContext context)
        {
            productImages = context.GetProductImages(product);
            InitializeComponent();
            Name.Content = product.Name;
            Description.Content = product.Description;
            Category.Content = product.CategoryName;
            Price.Content = product.Price;
            Image.Content = productImages.Count == 0 ? "Url" : productImages[0].Url;
            currentImageIndex = 0;
        }

        private void Next_Click(object sender, RoutedEventArgs e)
        {
            if (productImages.Count == 0) return;
            CalculateIndex(true);
            Image.Content = productImages[currentImageIndex].Url;
        }

        private void Prev_Click(object sender, RoutedEventArgs e)
        {
            if (productImages.Count == 0) return;
            CalculateIndex(false);
            Image.Content = productImages[currentImageIndex].Url;
        }

        private void CalculateIndex(bool next)
        {
            if (next)
            {
                currentImageIndex = Image.Content.Equals(productImages.Last().Url) ? 0 : currentImageIndex + 1;
            }
            else
            {
                currentImageIndex = Image.Content.Equals(productImages.First().Url) ?
                                    productImages.Count - 1 : currentImageIndex - 1;
            }
        }
    }
}
