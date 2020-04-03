using System;

namespace LR3
{
    class Program
    {
        static void SetArr(Man[] arr)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                arr[i] = new Man();
                Console.Write("Enter name: ");
                arr[i].Name = Console.ReadLine();
                Console.Write("Enter age: ");
                arr[i].Age = CheckInt();
                Console.Write("Enter country: ");
                arr[i].Country = Console.ReadLine();
            }

            for (int i = 0; i < arr.Length; i++)
            {
                Console.WriteLine((i + 1) + ". " + arr[i]);
            }
        }

        static int CheckInt()
        {
            int a;
            while (!int.TryParse(Console.ReadLine(), out a) || a <= 0)
            {
                Console.Write("Incorrect data, try again: ");
            }
            return a;
        }

        static void Main()
        {
            Man obja = new Man();
            Man objb = new Man("J", 18, "B");
            Console.WriteLine(obja + "\n");
            Console.WriteLine(objb + "\n");

            Man[] arr = new Man[2];
            SetArr(arr);
            Console.WriteLine();
        }
    }
}
