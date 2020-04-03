namespace LR8
{
    enum Rank
    {
        Junior3 = 1,
        Junior2,
        Junior1,
        Adult3,
        Adult2,
        Adult1,
        CMS,
        MS,
        IMS,
        HMS
    }
 
    abstract class Sport : Person
    {
        public int Age { get; set; }
        public Rank @Rank { get; set; }

        public Sport() : base()
        {
            Age = 17;
            Rank = Rank.CMS;
        }

        public Sport(string n, string c, int a, Rank r) : base(n, c)
        {
            Age = a;
            Rank = r;
        }

        public override string ToString() => base.ToString() + $"\nAge: {Age}\nRank: {Rank}";
    }
}
