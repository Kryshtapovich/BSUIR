using System;
using System.Text;

namespace LR2
{
    class Task2
    {
        static void Main(string[] args)
        {
            Console.Write("Введите строку: ");
            StringBuilder str = new StringBuilder(Console.ReadLine());
            for (int i = 0; i < str.Length; i++)
            {
                if (char.IsUpper(str[i]) && (str[i] < 65 || str[i] > 90)) Console.Write(str[i] + " ");
            }
            Console.WriteLine();
        }
    }
}
