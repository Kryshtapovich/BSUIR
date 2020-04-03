using System;

namespace LR6
{
    abstract class Person
    {
        public string Name { get; set; }
        public string Country { get; set; }
        protected string ID { get; set; }

        public Person()
        {
            Name = "M";
            Country = "B";
            ID = GenID();
        }

        public Person(string n, string c)
        {
            Name = n;
            Country = c;
            ID = GenID();
        }

        protected static string GenID() => Guid.NewGuid().ToString();

        public override string ToString() => $"Name: {Name}\nCountry: {Country}\nID: {ID}";
    }
}
