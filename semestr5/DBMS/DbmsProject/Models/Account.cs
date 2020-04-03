using System;

namespace DbmsProject.Models
{
    public class Account
    {
        public Account() { }

        public Guid Id { get; set; }
        public Role Role { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string Email { get; set; }
        public string PasswordHash { get; set; }
    }
}
