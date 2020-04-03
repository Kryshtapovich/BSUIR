using System;
using System.Collections.Generic;
using System.Linq;

namespace Task17
{
    class Program
    {

        static void Main(string[] args)
        {
            int num = 1087388483;
            int amount = int.Parse(Console.ReadLine());
            Dictionary<int, int> divisors1 = new Dictionary<int, int>
            {
                { 1021, 1031 * 1033 },
                { 1031, 1021 * 1033 },
                { 1033, 1021 * 1031 },
            };

            int[] divisors2 = { 1021, 1031, 1033 };

            int[] numbers = new int[amount];

            for (int i = 0; i < amount; i++)
            {
                numbers[i] = int.Parse(Console.ReadLine());
            }

            foreach (var div in divisors1)
            {
                if (numbers.Contains(div.Key) && numbers.Contains(div.Value))
                {
                    Console.WriteLine("YES");
                    return;
                }
            }

            if (numbers.Intersect(divisors2).Count() == 3 || numbers.Contains(num))
            {
                Console.WriteLine("YES");
                return;
            }

            Console.WriteLine("NO");
        }
    }
}
