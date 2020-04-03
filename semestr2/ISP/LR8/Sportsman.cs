using System;

namespace LR8
{
    delegate void MyDelegate();

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
            Sport = "Canoeing";
            cmp.date = new DateTime(2020, 07, 01);
            cmp.name = "Championship";
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

        public event MyDelegate Dope;

        public void TakeDope()
        {
            Name = Country = ID = Sport = cmp.name = "Disqualified";
            Age = 0;
            Rank = 0;
            cmp.date = default;
        }

        public void Violation() => Dope?.Invoke();

        public event MyDelegate Payment;

        public void TooYoung(MyDelegate del) => del();

        public void NotPaid()
        {
            Name = Country = ID = Sport = cmp.name = "Not allowed";
            Age = 0;
            Rank = 0;
            cmp.date = default;
        }

        public void NotAllowed() => Payment?.Invoke();

    }
}