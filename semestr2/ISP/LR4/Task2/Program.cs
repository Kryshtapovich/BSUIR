using System;
using System.Runtime.InteropServices;

namespace Task2
{
    class Program
    {
        [DllImport("DLL.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int Add(int a, int b);

        [DllImport("Dll.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int Sub(int a, int b);

        [DllImport("Dll.dll", CallingConvention = CallingConvention.StdCall)]
        static extern float Average(float a, float b);

        [DllImport("Dll.dll", CallingConvention = CallingConvention.StdCall)]
        static extern int Mult(int a, int b);

        [DllImport("Dll.dll", CallingConvention = CallingConvention.StdCall)]
        static extern float Div(float a, float b);

        [DllImport("Dll.dll", CallingConvention = CallingConvention.Cdecl)] 
        static extern int Factorial(int a);

        [DllImport("Dll.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int Power(int a, int b);

        public static int Check()
        {
            int a;
            while(!int.TryParse(Console.ReadLine(), out a) || a <= 0 || a > 11)
            {
                Console.Write("Incorrect data, repeat: ");
            }
            return a;
        }

        static void Main(string[] args)
        {
            Console.Write("Enter a: ");
            int a = Check();
            Console.Write("Enter b: ");
            int b = Check();
            Console.WriteLine($"a = {a}\nb = {b}");
            Console.WriteLine("a + b = " + Add(a, b));
            Console.WriteLine("a - b = " + Sub(a, b));
            Console.WriteLine("Average: " + Average((float)a, (float)b));
            Console.WriteLine("a * b = " + Mult(a, b));
            Console.WriteLine("a / b = " + Div((float)a, (float)b));
            Console.WriteLine("b / a = " + Div((float)b, (float)a));
            Console.WriteLine("a! = " + Factorial(a));
            Console.WriteLine("b! = " + Factorial(b));
            Console.WriteLine("a^b = " + Power(a, b));
            Console.WriteLine("b^a = " + Power(b, a));
        }
    }
}
