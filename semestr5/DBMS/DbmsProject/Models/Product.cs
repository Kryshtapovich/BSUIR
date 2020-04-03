using System;

namespace DbmsProject.Models
{
    public class Product
    {
        public Product() { }

        public Guid Id { get; set; }
        public string CategoryName { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public decimal Price { get; set; }
    }
}
