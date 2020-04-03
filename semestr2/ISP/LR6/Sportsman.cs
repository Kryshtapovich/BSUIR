using System;

namespace LR6
{
    class Sportsman : Sport, IComparable, ICloneable, ICompetitions
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

        int IComparable.CompareTo(object obj)
        {
            if (this.Age > ((Sportsman)obj).Age) return 1;
            if (this.Age < ((Sportsman)obj).Age) return -1;
            else return 0;
        }

        public object Clone() => (Sportsman)this.MemberwiseClone();

        public void Dope()
        {
            Name = Country = ID = Sport = cmp.name = "Disqualified";
            Age = 0;
            Rank = 0;
            cmp.date = default;
        }

        public void Payment()
        {
            Name = Country = ID = Sport = cmp.name = "Not allowed";
            Age = 0;
            Rank = 0;
            cmp.date = default;
        }
    }
}
