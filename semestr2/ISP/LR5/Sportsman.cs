using System;

namespace LR5
{
    class Sportsman : Sport
    {
        public string Sport { get; set; }

        public struct Comp
        {
            public DateTime date;
            public string name;
        }

        public Comp cmp;

        public Sportsman() : base()
        {
            Sport = "C";
            cmp.date = new DateTime(2020, 07, 01);
            cmp.name = "C";
        }

        public Sportsman(string n = "", string c = "", int a = 0, string s = "", Rank r = default, string cn = "", DateTime date = default) : base(n, c, a, r)
        {
            Sport = s;
            cmp.name = cn;
            cmp.date = date;
        }

        public override string ToString() => base.ToString() + $"\nSport: {Sport}\nCompetitions: {cmp.name}\t{cmp.date.ToString("d")}\n";
    }
}
