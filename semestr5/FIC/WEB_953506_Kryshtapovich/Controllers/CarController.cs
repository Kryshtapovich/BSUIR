using System.Linq;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using WEB_953506_Kryshtapovich.Data;
using WEB_953506_Kryshtapovich.Entities;
using WEB_953506_Kryshtapovich.Extensions;
using WEB_953506_Kryshtapovich.Models;

namespace WEB_953506_Kryshtapovich.Controllers
{
    public class CarController : Controller
    {
        private int pageSize;
        private ApplicationDbContext context;
        private ILogger logger;
        public CarController(ApplicationDbContext context, ILogger<CartController> logger)
        {
            pageSize = 3;
            this.context = context;
            this.logger = logger;
        }

        [Route("Catalog")]
        [Route("Catalog/Page_{page}")]
        public IActionResult Index(int? carClass, int page = 1)
        {
            ViewData["Classes"] = context.CarClasses;
            ViewData["CurrentClass"] = carClass ?? 0;

            logger.LogInformation($"info: carClass={carClass}, page={page}");

            var filteredCars = context.Cars.Where(car => !carClass.HasValue || car.ClassId == carClass);
            var model = ListViewModel<Car>.Get(filteredCars, page, pageSize);

            return Request.IsAjaxRequest() ? PartialView("_listpartial", model) : View(model);
        }
    }
}