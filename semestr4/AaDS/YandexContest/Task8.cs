using System;
using System.Linq;

namespace Task8
{
    class Program
    {
        
        static bool IsPalindrome(string str)
        {
            for (int i = 0; i < str.Length / 2; i++)
            {
                if (str[i] != str[str.Length - i - 1])
                {
                    return false;
                }
            }
            return true;
        }

        static void Main(string[] args)
        {
            string str = Console.ReadLine();

            if(str.All(x => x == str[0]))
            {
                Console.WriteLine(-1);
            }
            else if (IsPalindrome(str))
            {
                Console.WriteLine(str.Length - 1);
            }
            else
            {
                Console.WriteLine(str.Length);
            }
        }
    }
}