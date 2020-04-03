using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;
using WEB_953506_Kryshtapovich.Entities;

namespace WEB_953506_Kryshtapovich.Data
{
    public class DbInitializer
    {
        public static async Task Init(ApplicationDbContext context,
                                        UserManager<ApplicationUser> userManager,
                                        RoleManager<IdentityRole> roleManager)
        {
            context.Database.EnsureCreated();
            if (!context.Roles.Any())
            {
                var adminRole = new IdentityRole
                {
                    Name = "admin",
                    NormalizedName = "admin"
                };
                await roleManager.CreateAsync(adminRole);
            }

            if (!context.Users.Any())
            {
                var user = new ApplicationUser
                {
                    Email = "user@user.user",
                    UserName = "user"
                };
                await userManager.CreateAsync(user, "user123");

                var admin = new ApplicationUser
                {
                    Email = "admin@admin.admin",
                    UserName = "admin"
                };
                await userManager.CreateAsync(admin, "admin123");
                await userManager.AddToRoleAsync(admin, "admin");
                await context.SaveChangesAsync();
            }

            if (!context.CarClasses.Any())
            {
                context.CarClasses.AddRange(
                    new List<CarClass>
                    {
                        new CarClass{Name="Coupe"},
                        new CarClass{Name="Fastback"},
                        new CarClass{Name="Pickup"},
                        new CarClass{Name="Crossover"}
                    });
                await context.SaveChangesAsync();
            }

            if (!context.Cars.Any())
            {
                context.Cars.AddRange(
                    new List<Car>
                    {
                        new Car{Name="Lamborghini Aventador", Description="Too fast, too furious",
                        Price=300000, ClassId=1, Image="aventador.jpg"},
                        new Car{Name="Audi RS7", Description="Fast luxury",
                        Price=150000, ClassId=2, Image="audi.jpg"},
                        new Car{Name="Ford Mustang", Description="Legenary beast",
                        Price=35000, ClassId=1, Image="mustang.jpg"},
                        new Car{Name="Ford Raptor", Description="Huge car for off-road",
                        Price=50000, ClassId=3, Image="raptor.jpg"},
                        new Car{Name="Lamborghini Urus", Description="Itallian monster",
                        Price=450000, ClassId=4, Image="urus.jpg"},
                    });
                await context.SaveChangesAsync();
            }
        }
    }
}