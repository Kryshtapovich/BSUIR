using System;
using System.Linq;

namespace Task7
{
    class Program
    {
        static int[] ParseString(string str)
        {
            return str.Split().Select(x => int.Parse(x)).ToArray();
        }

        static void Main(string[] args)
        {
            var data = ParseString(Console.ReadLine());

            int x1 = data[2];
            int y1 = data[3];
            int x2 = data[4];
            int y2 = data[5];

            if(Math.Abs(x1 - x2) == Math.Abs(y1 - y2))
            {
                Console.WriteLine("NO");
            }
            else
            {
                Console.WriteLine("YES");
            }
        }
    }
}
