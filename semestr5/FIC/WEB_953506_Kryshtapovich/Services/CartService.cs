
using System;
using System.Text.Json.Serialization;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using WEB_953506_Kryshtapovich.Entities;
using WEB_953506_Kryshtapovich.Extensions;
using WEB_953506_Kryshtapovich.Models;

namespace WEB_953506_Kryshtapovich.Services
{
    public class CartService : Cart
    {
        private string sessionKey = "cart";

        [JsonIgnore]
        ISession Session {get;set;}

        public static Cart GetCart(IServiceProvider serviceProvider)
        {
            var session = serviceProvider.GetRequiredService<IHttpContextAccessor>()
                                         .HttpContext
                                         .Session;
            
            var cart = session?.Get<CartService>("cart") ?? new CartService();
            cart.Session = session;
            return cart;
        }

        public override void AddToCart(Car car)
        {
            base.AddToCart(car);
            Session?.Set<CartService>(sessionKey, this);
        }

        public override void RemoveFromCart(int id)
        {
            base.RemoveFromCart(id);
            Session?.Set<CartService>(sessionKey, this);
        }

        public override void ClearAll()
        {
            base.ClearAll();
            Session?.Set<CartService>(sessionKey, this);
        }
    }
}