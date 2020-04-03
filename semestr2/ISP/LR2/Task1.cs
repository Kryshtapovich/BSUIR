using System;

namespace LR2
{
    class Task1
    {
        static void Counter(string str, char a)
        {
            int count = 0;
            for (int i = 0; i < str.Length; i++)
            {
                if (str[i] == a) count++;
            }
            Console.WriteLine("Цифр " + a + ": " + count);
        }

        static void DigitsInDate(string str)
        {
            for (char i = '0'; i <= '9'; i++)
            {
                Counter(str, i);
            }
        }

        static void Main(string[] args)
        {
            string full = DateTime.Now.ToString("F");
            string sh = DateTime.Now.ToString("g");
            Console.WriteLine("Полный формат текущей даты: " + full);
            DigitsInDate(full);
            Console.WriteLine("\nКраткий формат текущей даты: " + sh);
            DigitsInDate(sh);
        }
    }
}
