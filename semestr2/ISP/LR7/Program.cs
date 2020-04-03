using System;

namespace LR7
{
    class Program
    {
        public static int CheckNat()
        {
            int a;
            while (!int.TryParse(Console.ReadLine(), out a) || a <= 0)
                Console.Write("Incorrect input, repeat: ");
            return a;
        }

        public static int CheckInt()
        {
            int a;
            while (!int.TryParse(Console.ReadLine(), out a))
                Console.Write("Incorrect input, repeat: ");
            return a;
        }

        public static double CheckDouble()
        {
            double a;
            while (!double.TryParse(Console.ReadLine(), out a))
                Console.Write("Incorrect input, repeat: ");
            return a;
        }

        public static bool CheckFraction(string frac)
        {
            for (int i = 0; i < frac.Length; i++)
            {
                if (i == 0 && frac[i] == '-') i++;
                if (frac[i] == '/' && i != frac.Length - 1) i++;
                if (!char.IsDigit(frac[i]) || (frac[i] == '0' && i == frac.Length - 1 && frac[i - 1] == '/')) return false;
            }
            return true;
        }

        public static Number GetNumber()
        {
            Console.Write("Number: ");
            double number = CheckDouble();
            return new Number(number);
        }

        public static Number GetFraction()
        {
            Console.Write("Fraction: ");
            string str = Console.ReadLine();
            while (!CheckFraction(str))
            {
                Console.Write("Incorrect input, repeat: ");
                str = Console.ReadLine();
            }

            try
            {
                string[] arr = str.Split('/');
                return new Number(int.Parse(arr[0]), int.Parse(arr[1]));
            }
            catch
            {
                return new Number(int.Parse(str), 1);
            }
        }

        public static Number Enter()
        {
            int a;
            Console.Write(" (0 - Fraction, 1 - Number): ");
            while (!int.TryParse(Console.ReadLine(), out a) || a < 0 || a > 1)
                Console.Write("Incorrect input, repeat: ");
            if (a == 0) return GetFraction();
            else return GetNumber();
        }

        static void Main(string[] args)
        {
            Console.Write("Enter the first number");
            var num1 = Enter();
            Console.Write("Enter the second number");
            var num2 = Enter();
            Console.Clear();
            Console.WriteLine("The first number:\n" + num1);
            Console.WriteLine("The second number:\n" + num2);
            Console.WriteLine($"1. {num1.ShowAsFraction} > {num2.ShowAsFraction} = " + (num1 > num2));
            Console.WriteLine($"   {num1.ShowAsNumber} > {num2.ShowAsNumber} = " + (num1 > num2) + "\n");
            Console.WriteLine($"2. {num1.ShowAsFraction} < {num2.ShowAsFraction} = " + (num1 < num2));
            Console.WriteLine($"   {num1.ShowAsNumber} < {num2.ShowAsNumber} = " + (num1 < num2) + "\n");
            Console.WriteLine($"3. {num1.ShowAsFraction} == {num2.ShowAsFraction} = " + (num1 == num2));
            Console.WriteLine($"   {num1.ShowAsNumber} == {num2.ShowAsNumber} = " + (num1 == num2) + "\n");
            Console.WriteLine($"4. {num1.ShowAsFraction} != {num2.ShowAsFraction} = " + (num1 != num2));
            Console.WriteLine($"   {num1.ShowAsNumber} != {num2.ShowAsNumber} = " + (num1 != num2) + "\n");
            Console.WriteLine($"5. {num1.ShowAsFraction} + {num2.ShowAsFraction} = " + (num1 + num2).ShowAsFraction);
            Console.WriteLine($"   {num1.ShowAsNumber} + {num2.ShowAsNumber} = " + (num1 + num2).ShowAsNumber + "\n");
            Console.WriteLine($"6. {num1.ShowAsFraction} - {num2.ShowAsFraction} = " + (num1 - num2).ShowAsFraction);
            Console.WriteLine($"   {num1.ShowAsNumber} - {num2.ShowAsNumber} = " + (num1 - num2).ShowAsNumber + "\n");
            Console.WriteLine($"7. {num1.ShowAsFraction} * {num2.ShowAsFraction} = " + (num1 * num2).ShowAsFraction);
            Console.WriteLine($"   {num1.ShowAsNumber} * {num2.ShowAsNumber} = " + (num1 * num2).ShowAsNumber + "\n");
            if (num2 != 0)
            {
                Console.WriteLine($"8. {num1.ShowAsFraction} / {num2.ShowAsFraction} = " + (num1 / num2).ShowAsFraction);
                Console.WriteLine($"   {num1.ShowAsNumber} / {num2.ShowAsNumber} = " + (num1 / num2).ShowAsNumber + "\n");
            }
        }
    }
}
