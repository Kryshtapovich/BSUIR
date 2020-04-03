using Microsoft.AspNetCore.Mvc;
using WEB_953506_Kryshtapovich.Data;
using WEB_953506_Kryshtapovich.Models;
using Microsoft.AspNetCore.Authorization;

namespace WEB_953506_Kryshtapovich.Controllers
{
    public class CartController : Controller
    {
        private ApplicationDbContext context;
        private Cart cart;

        public CartController(ApplicationDbContext context, Cart cart)
        {
            this.context = context;
            this.cart = cart;
        }
        
        public IActionResult Index()
        {
            return View(cart.Items.Values);
        }
    
        [Authorize]
        public IActionResult Add(int id, string returnUrl)
        {
            var item = context.Cars.Find(id);
            if(item != null)
            {
                cart.AddToCart(item);
            }
            return Redirect(returnUrl);
        }

        public IActionResult Delete(int id)
        {
            cart.RemoveFromCart(id);
            return RedirectToAction("Index");
        }
    }
}