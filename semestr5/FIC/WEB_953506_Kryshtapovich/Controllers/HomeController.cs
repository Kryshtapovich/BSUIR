using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using System.Collections.Generic;
using System.Diagnostics;
using WEB_953506_Kryshtapovich.Models;

namespace WEB_953506_Kryshtapovich.Controllers
{
    public class HomeController : Controller
    {
        class ListDemo
        {
            public int ListItemValue { get; set; }
            public string ListItemText { get; set; }
        }

        private List<ListDemo> listDemos;

        public HomeController()
        {
            listDemos = new List<ListDemo>
            {
                new ListDemo{ListItemValue=1, ListItemText="Item 1"},
                new ListDemo{ListItemValue=2, ListItemText="Item 2"},
                new ListDemo{ListItemValue=3, ListItemText="Item 3"},
            };
        }

        public IActionResult Index()
        {
            ViewData["Lst"] = new SelectList(listDemos, "ListItemValue", "ListItemText");
            ViewData["Text"] = "Лабораторная работа 2";
            return View();
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
