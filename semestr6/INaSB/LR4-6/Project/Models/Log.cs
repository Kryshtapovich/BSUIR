using System;

namespace DbmsProject.Models
{
    public class Log
    {
        public Log() { }

        public Guid Id { get; set; }
        public string Info { get; set; }
        public DateTime Date { get; set; }
    }
}
