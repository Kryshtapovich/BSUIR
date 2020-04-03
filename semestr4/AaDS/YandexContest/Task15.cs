using System;
using System.Linq;

namespace Task15
{
    class Program
    {
        static int[] ParseString(string str) => str.Split().Select(x => int.Parse(x)).ToArray();

        static void Main(string[] args)
        {
            Console.ReadLine();
            int[] arr = ParseString(Console.ReadLine());

            int max = arr.Max();
            long count = 0;

            for (int i = 0; i < arr.Length - 1; i++)
            {
                if (arr[i + 1] > arr[i])
                {
                    int temp = max - arr[i];
                    count += temp;
                    for (int j = i; j < arr.Length && temp != 0; j++)
                    {
                        if (temp > max - arr[j])
                        {
                            temp = max - arr[j];
                        }
                        arr[j] += temp;
                    }
                }
            }

            count += max - arr.Last();
            Console.WriteLine(count);
        }
    }
}