using System;

namespace DbmsProject.Models
{
    public class Image
    {
        public Image () { }

        public Guid Id { get; set; }
        public Guid ProductId { get; set; }
        public string Url { get; set; }
    }
}
