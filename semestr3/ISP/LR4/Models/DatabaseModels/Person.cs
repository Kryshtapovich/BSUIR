using System;

namespace Models
{
    [Serializable]
    public class Person
    {
        public string Name { get; set; }

        public string Surname { get; set; }

        public string Email { get; set; }

        public string PhoneNumber { get; set; }

        public string State { get; set; }

        public string City { get; set; }

        public string Address { get; set; }
    }
}
