using System;
using System.Collections.Generic;
using System.Linq;

namespace Task16
{
    class Program
    {

        static void Main(string[] args)
        {
            string num = Console.ReadLine();
            char[] arr = num.ToCharArray();
            List<char> lst = new List<char>();
            for (int i = arr.Length - 1; i >= 1; i--)
            {
                if (arr[i - 1] < arr[i])
                {
                    for (int j = i; j < arr.Length; j++)
                    {
                        lst.Add(arr[j]);
                    }
                    char max = lst.Last(x => x > arr[i - 1]);
                    char next = arr[i - 1];
                    arr[i - 1] = max;
                    lst.Remove(max);
                    lst.Add(next);
                    lst.Sort();
                    for (int j = arr.Length - 1, z = lst.Count - 1; j >= i; j--, z--)
                    {
                        arr[j] = lst[z];
                    }
                    break;
                }
            }
            string res = new string(arr);
            if (arr[0] == '0' || res == num)
            {
                Console.WriteLine(-1);
            }
            else
            {
                Console.WriteLine(res);
            }
        }
    }
}
