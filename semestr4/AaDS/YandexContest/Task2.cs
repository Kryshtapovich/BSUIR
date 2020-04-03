using System;
using System.Linq;

namespace Task2
{
    class Program
    {
        static long[] ParseString(string str)
        {
            return str.Split().Select(x => long.Parse(x)).ToArray();
        }

        static void Main(string[] args)
        {
            Console.ReadLine();
            long[] numbers = ParseString(Console.ReadLine());

            Array.Sort(numbers);

            long pos1 = numbers[numbers.Length - 1];
            long pos2 = numbers[numbers.Length - 2];

            long neg1 = numbers[0];
            long neg2 = numbers[1];

            Console.WriteLine(Math.Max(pos1 * pos2, neg1 * neg2));
         }
     }
}