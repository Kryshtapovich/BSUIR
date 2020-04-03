using System;

namespace LR2
{
    class Task3
    {
        static float CheckFloat()
        {
            float a;
            while (!float.TryParse(Console.ReadLine(), out a) || a <= 0)
                Console.Write("Некорректные данные, попробуйте еще раз: ");
            return a;
        }

        static bool Check(float a, float b, float c)
        {
            if (a < b + c && b < a + c && c < a + b) return true;
            else return false;
        }

        static float Perimetr(float a, float b, float c) => a + b + c;

        static float Square(float a, float b, float c)
        {
            float p = Perimetr(a, b, c) / 2;
            return (float)Math.Sqrt(p * (p - a) * (p - b) * (p - c));
        }

        static float RadiusOut(float a, float b, float c) => (a * b * c) / (4 * Square(a, b, c));

        static float RadiusIn(float a, float b, float c) => (Square(a, b, c) / (Perimetr(a, b, c) / 2));

        static void Angles(float a, float b, float c)
        {
            float x = (b * b + c * c - a * a) / (2 * b * c);
            float y = (a * a + c * c - b * b) / (2 * a * c);
            float z = (a * a + b * b - c * c) / (2 * a * b);
            Console.WriteLine("Первый угол равен: " + (Math.Acos(x) * 180 / Math.PI));
            Console.WriteLine("Второй угол равен: " + (Math.Acos(y) * 180 / Math.PI));
            Console.WriteLine("Третий угол равен: " + (Math.Acos(z) * 180 / Math.PI));
        }

        static void Main(string[] args)
        {
            Console.Write("Введите первую сторону треугольника: ");
            float a = CheckFloat();
            Console.Write("Введите вторую сторону треугольника: ");
            float b = CheckFloat();
            Console.Write("Введите третюю сторону треугольника: ");
            float c = CheckFloat();
            if (Check(a, b, c))
            {
                Console.WriteLine("Периметр: " + (a + b + c));
                Console.WriteLine("Площадь: " + Square(a, b, c));
                Console.WriteLine("Радиус описанной окружности: " + RadiusOut(a, b, c));
                Console.WriteLine("Радиус вписанной окружности: " + RadiusIn(a, b, c));
                Angles(a, b, c);
            }
            else
            {
                Console.WriteLine("Такого треугольника не существует");
            }
        }
    }
}
