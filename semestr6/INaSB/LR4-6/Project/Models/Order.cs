using System;

namespace DbmsProject.Models
{
    public class Order
    {
        public Order() { }

        public Guid Id { get; set; }
        public string ProductName { get; set; }
        public string StoreName { get; set; }
        public DateTime Date { get; set; }
    }
}
