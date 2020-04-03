using System;
using System.Linq;

namespace Task9
{
    class Program
    {
        static int[] ParseString(string str) => str.Split().Select(x => int.Parse(x)).ToArray();

        static void Invert(ref char ch) => ch = Char.IsUpper(ch) ? Char.ToLower(ch) : Char.ToUpper(ch);

        static void Main(string[] args)
        {
            char[] str = Console.ReadLine().ToCharArray();
            int q = Convert.ToInt32(Console.ReadLine());
            bool[] inversionIntervals = new bool[str.Length + 1];


            for (int i = 0; i < q; i++)
            {
                int[] interval = ParseString(Console.ReadLine());
                int left = interval[0];
                int right = interval[1];

                if(left != right)
                {
                	if (left > right)
                    {
                        int tmp = left;
                        left = right;
                        right = tmp;
                    }
                	
                    inversionIntervals[--left] = !inversionIntervals[left];
                    inversionIntervals[right] = !inversionIntervals[right];
                }
                else
                {
                    Invert(ref str[--left]);
                }
            }

            bool needInvert = false;

            for (int i = 0; i < str.Length; i++)
            {
                if (inversionIntervals[i])
                {
                    needInvert = !needInvert;
                }

                if (needInvert)
                {
                    Invert(ref str[i]);
                }
            }

            Console.WriteLine(new string(str));
        }
    }
}

