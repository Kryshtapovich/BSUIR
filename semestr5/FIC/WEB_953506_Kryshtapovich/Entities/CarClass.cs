using System.Collections.Generic;

namespace WEB_953506_Kryshtapovich.Entities
{
    public class CarClass
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public List<Car> Cars { get; set; }
    }
}