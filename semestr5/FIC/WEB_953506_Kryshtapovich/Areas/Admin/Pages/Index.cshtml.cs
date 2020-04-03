using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using WEB_953506_Kryshtapovich.Data;
using WEB_953506_Kryshtapovich.Entities;

namespace WEB_953506_Kryshtapovich.Areas.Admin.Pages
{
    public class IndexModel : PageModel
    {
        private readonly WEB_953506_Kryshtapovich.Data.ApplicationDbContext _context;

        public IndexModel(WEB_953506_Kryshtapovich.Data.ApplicationDbContext context)
        {
            _context = context;
        }

        public IList<Car> Car { get;set; }

        public async Task OnGetAsync()
        {
            Car = await _context.Cars.ToListAsync();
        }
    }
}
