using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using WEB_953506_Kryshtapovich.Entities;

namespace WEB_953506_Kryshtapovich.Controllers
{
    public class ImageController : Controller
    {
        private UserManager<ApplicationUser> userManager;
        private IWebHostEnvironment environment;

        public ImageController(UserManager<ApplicationUser> userManager, IWebHostEnvironment environment)
        {
            this.userManager = userManager;
            this.environment = environment;
        }

        public async Task<FileResult> GetAvatar()
        {
            var user = await userManager.GetUserAsync(User);
            if (user.AvatarImage != null)
            {
                return File(user.AvatarImage, "image/...");
            }
            else
            {
                var avatarPath = "/Images/anonymous.png";
                return File(environment.WebRootFileProvider.GetFileInfo(avatarPath).CreateReadStream(), "image/...");
            }
        }
    }
}