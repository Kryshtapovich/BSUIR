using System;

namespace LR3
{
    class Person
    {
        public string Name { get; set; }
        public int Age { get; set; }
        public string Country { get; set; }
        protected string ID { get; set; }

        public Person()
        {
            Name = "M";
            Age = 17;
            Country = "B";
            ID = GenID();
        }

        public Person(string n = "", int a = 0, string c = "")
        {
            Name = n;
            Age = a;
            Country = c;
            ID = GenID();
        }

        protected static string GenID() => Guid.NewGuid().ToString();

        public override string ToString() => $"Name: {Name}\nAge: {Age}\nCountry: {Country}\nID: {ID}";
    }
}
