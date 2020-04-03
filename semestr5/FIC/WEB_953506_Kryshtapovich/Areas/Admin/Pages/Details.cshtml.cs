﻿using System;
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
    public class DetailsModel : PageModel
    {
        private readonly WEB_953506_Kryshtapovich.Data.ApplicationDbContext _context;

        public DetailsModel(WEB_953506_Kryshtapovich.Data.ApplicationDbContext context)
        {
            _context = context;
        }

        public Car Car { get; set; }

        public async Task<IActionResult> OnGetAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            Car = await _context.Cars.FirstOrDefaultAsync(m => m.Id == id);

            if (Car == null)
            {
                return NotFound();
            }
            return Page();
        }
    }
}
