using System.Collections.Generic;
using System.Linq;
using WEB_953506_Kryshtapovich.Entities;

namespace WEB_953506_Kryshtapovich.Models
{
    public class Cart
    {
        public Dictionary<int, CartItem> Items {get;set;}
        public Cart() 
        {
            Items = new Dictionary<int, CartItem>();
        }

        public int Count =>  Items.Sum(item => item.Value.Quantity);
        
        public int Price => Items.Sum(item => item.Value.Quantity * item.Value.Car.Price);

        public virtual void AddToCart(Car car)
        {
            if(Items.ContainsKey(car.Id))
            {
                Items[car.Id].Quantity++;
            }
            else
            {
                Items.Add(car.Id, new CartItem
                {
                    Car = car,
                    Quantity = 1
                });
            }
        }

        public virtual void RemoveFromCart(int id)
        {
            Items.Remove(id);
        }

        public virtual void ClearAll()
        {
            Items.Clear();
        }
    }

    public class CartItem
    {
        public Car Car { get; set; }
        public int Quantity { get; set; }
    }
}