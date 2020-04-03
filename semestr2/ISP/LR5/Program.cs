using System;

namespace LR5
{

    class Program
    {
        public static int CheckAge()
        {
            int a;
            while (!int.TryParse(Console.ReadLine(), out a) || a <= 0)
                Console.Write("Incorrect input, repeat: ");
            return a;
        }

        public static int CheckRank()
        {
            int a;
            while (!int.TryParse(Console.ReadLine(), out a) || a < 1 || a > 10)
                Console.Write("Incorrect input, repeat: ");
            return a;
        }

        public static DateTime CheckDate()
        {
            DateTime date;
            while (!DateTime.TryParse(Console.ReadLine(), out date))
                Console.Write("Incorrect input, repeat: ");
            return date;
        }

        public static Sportsman SetSportsman()
        {
            Console.Write("Enter name: ");
            string name = Console.ReadLine();
            Console.Write("Enter the country: ");
            string country = Console.ReadLine();
            Console.Write("Enter the age: ");
            int age = CheckAge();
            Console.Write("Enter the sport: ");
            string sport = Console.ReadLine();
            Console.Write("Enter the sport rank(1 - Junior3, 2 - Junior2, 3 - Junior1, 4 - Adult3, 5 - Adult2, 6 - Adult1, 7 - CMS, 8 - MS, 9 - IMS, 10 - HMS): ");
            int rank = CheckRank();
            Console.Write("Enter the name of competitions: ");
            string compname = Console.ReadLine();
            Console.Write("Enter the date of copmetitions: ");
            DateTime date = CheckDate();
            return new Sportsman(name, country, age, sport, (Rank)rank, compname, date);
        }

        public static void SetList(Sportsman [] list)
        {
            for (int i = 0; i < list.Length; i++)
                list[i] = SetSportsman();
            Console.Clear();
            Console.WriteLine("List of spotsmen:");
            for (int i = 0; i < list.Length; i++)
                Console.WriteLine(list[i]);
        }

        static void Main(string[] args)
        {
            Sportsman obja = new Sportsman();
            Sportsman objb = new Sportsman("Vasiliy", "Russia", 19, "Football", Rank.MS, "Europe Championship", new DateTime(2020, 08, 01));
            var objc = SetSportsman();
            Console.Clear();
            Console.WriteLine(obja);
            Console.WriteLine(objb);
            Console.WriteLine(objc);

            Sportsman[] list = new Sportsman[2];
            SetList(list);
        }
    }
}
