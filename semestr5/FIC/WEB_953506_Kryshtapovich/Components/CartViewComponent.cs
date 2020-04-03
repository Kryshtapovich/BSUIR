using Microsoft.AspNetCore.Mvc;
using WEB_953506_Kryshtapovich.Models;

namespace WEB_953506_Kryshtapovich.Components
{
    public class CartViewComponent : ViewComponent
    {
        private Cart cart;

        public CartViewComponent(Cart cart)
        {
            this.cart = cart;
        }

        public IViewComponentResult Invoke()
        {   
            return View(cart);
        }
    }
}