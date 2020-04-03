using System;
using System.Linq;

namespace Task3
{
    class Program
    {
        static long[] ParseString(string str)
        {
            return str.Split().Select(x => long.Parse(x)).ToArray();
        }

        static void Main(string[] args)
        {

            long k = ParseString(Console.ReadLine())[1];
            long[] numbers = ParseString(Console.ReadLine());
            long mod = (long)Math.Pow(10, 9) + 7;
            Array.Sort(numbers);

            long res = 1;

            int i = 0;
            int j = numbers.Length - 1;

            if (k % 2 != 0)
            {
                res *= numbers[j] % mod;
                j--;
                k--;
            }

            for (int z = 0; z < k / 2; z++)
            {
                long left = numbers[i] * numbers[i + 1];
                long right = numbers[j] * numbers[j - 1];

                if (left > right && res > 0 || left <= right && res <= 0)
                {
                    res *= left % mod;
                    res %= mod;
                    i += 2;
                }
                else
                {
                    res *= right % mod;
                    res %= mod;
                    j -= 2;
                }
            }

            if (res < 0)
            {
                res += mod;
            }

            Console.WriteLine(res);
        }
    }
}

