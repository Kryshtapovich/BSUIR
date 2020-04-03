using System;

namespace LR8
{
    class Program
    {
        public static void Waiting()
        {
            Console.Write("Enter the next button: ");
            Console.ReadKey();
            Console.WriteLine("\n");
        }

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

        public static int CheckCompetitions()
        {
            int comp;
            while (!int.TryParse(Console.ReadLine(), out comp) || comp < 0 || comp > 1)
                Console.Write("Incorrect input, repeat: ");
            return comp;
        }

        public static Sportsman SetSportsman()
        {
            Sportsman obj = new Sportsman();
            Console.Write("Enter name: ");
            obj.Name = Console.ReadLine();
            Console.Write("Enter the country: ");
            obj.Country = Console.ReadLine();
            Console.Write("Enter the age: ");
            obj.Age = CheckAge();
            if (obj.Age < 18)
            {
                obj.TooYoung(obj.NotPaid);
                return obj;
            }
            Console.Write("Enter the sport: ");
            obj.Sport = Console.ReadLine();
            Console.Write("Enter the sport rank(1 - Junior3, 2 - Junior2, 3 - Junior1, 4 - Adult3, 5 - Adult2, 6 - Adult1, 7 - CMS, 8 - MS, 9 - IMS, 10 - HMS): ");
            obj.Rank = (Rank)CheckRank();
            Console.Write("Enter the name of competitions: ");
            obj.cmp.name = Console.ReadLine();
            Console.Write("Enter the date of copmetitions: ");
            obj.cmp.date = CheckDate();
            Console.Write("Make a contribution? (0 - no, 1 - yes): ");
            int cont = CheckCompetitions();
            if (cont == 0)
            {
                obj.Payment += () => obj.NotPaid();
                obj.NotAllowed();
                return obj;
            }
            Console.Write("Take a dope? (0 - no,  1 - yes): ");
            int dope = CheckCompetitions();
            if (dope == 0) return obj;
            else
            {
                obj.Dope += delegate
                {
                    obj.TakeDope();
                };
                obj.Violation();
                return obj;
            }
        }

        public static void SetList(Sportsman[] list)
        {
            for (int i = 0; i < list.Length; i++)
                list[i] = SetSportsman();
            Console.Clear();
            Console.WriteLine("List of spotsmen:");
            for (int i = 0; i < list.Length; i++)
                Console.WriteLine(list[i]);
            Waiting();
        }

        static void Main(string[] args)
        {
            Sportsman sp = new Sportsman();
            Console.WriteLine(sp);
            Waiting();
            Sportsman[] list = new Sportsman[2];
            SetList(list);
            Console.Clear();
            Console.WriteLine("Sorted list:");
            Array.Sort(list);
            foreach (Sportsman s in list)
                Console.WriteLine(s);
            Waiting();
            Console.WriteLine("Copy of the first sportsman in the list:");
            Sportsman obj = (Sportsman)list[0].Clone();
            Console.WriteLine(obj);
        }
    }
}