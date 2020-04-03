using Microsoft.AspNetCore.Identity;

namespace WEB_953506_Kryshtapovich.Entities
{
    public class ApplicationUser : IdentityUser
    {
        public byte[] AvatarImage { get; set; }
    }
}