using System;

namespace LR7
{
    class Number : IEquatable<Number>, IComparable
    {
        public int Integer { get; set; }
        public int Natural { get; set; }
        double number;

        public Number()
        {
            Integer = 1;
            Natural = 1;
        }

        public Number(int i, int n)
        {
            Integer = i;
            Natural = n;
            number = (double)Integer / Natural;
        }

        public Number(double num)
        {
            number = num;
            int count = -1;
            if (num % 10 == 0)
            {
                Integer = (int)num;
                Natural = 1;
                number = num;
            }
            else
            {
                for (int i = 0; (float)num % 10 != 0 || Math.Abs(num) < 1; i++)
                {
                    num *= 10;
                    count++;
                }
                num /= 10;
                Integer = (int)num;
                Natural = (int)Math.Pow(10, count);
            }
        }

        public static Number operator +(Number num1, Number num2)
        {
            Number num = new Number();
            num.Integer = num1.Integer * num2.Natural + num2.Integer * num1.Natural;
            num.Natural = num1.Natural * num2.Natural;
            num.number = num1.number + num2.number;
            return num;
        }

        public static Number operator -(Number num1, Number num2)
        {
            Number num = new Number();
            num.Integer = num1.Integer * num2.Natural - num2.Integer * num1.Natural;
            num.Natural = num1.Natural * num2.Natural;
            num.number = num1.number - num2.number;
            return num;
        }

        public static Number operator *(Number num1, Number num2)
        {
            Number num = new Number();
            num.Integer = num1.Integer * num2.Integer;
            num.Natural = num1.Natural * num2.Natural;
            num.number = num1.number * num2.number;
            return num;
        }

        public static Number operator /(Number num1, Number num2)
        {
            Number num = new Number();
            num.Integer = num1.Integer * num2.Natural;
            num.Natural = num1.Natural * num2.Integer;
            if(num1 < 0 || num2 < 0)
            {
                num.Integer = -num.Integer;
                num.Natural = Math.Abs(num.Natural);
            }
            num.number = num1.number / num2.number;
            return num;
        }

        public static bool operator >(Number num1, Number num2) => num1.number > num2.number;
        
        public static bool operator <(Number num1, Number num2) => num1.number < num2.number;
       
        public static bool operator ==(Number num1, Number num2) => num1.Equals(num2);

        public static bool operator !=(Number num1, Number num2) => !num1.Equals(num2);
        
        public override bool Equals(object obj) => ((Number)obj).number == this.number;

        public override int GetHashCode() => this.ToString().GetHashCode();

        public static implicit operator int(Number num) => (int)num.number;

        public static implicit operator double(Number num) => num.number;

        bool IEquatable<Number>.Equals(Number num) => this.number == num.number;

        int IComparable.CompareTo(object obj)
        {
            if (this.number > ((Number)obj).number) return 1;
            if (this.number < ((Number)obj).number) return -1;
            else return 0;
        }

        public string ShowAsNumber => $"{number}";

        public string ShowAsFraction => $"{Integer}/{Natural}";

        public override string ToString() => "Number: " + ShowAsNumber + "\nFraction: " + ShowAsFraction + "\n";
    }
}