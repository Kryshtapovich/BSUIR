using System;
using System.IO;

namespace LR1
{
    class Program
    {
        public static float CheckFloat()
        {
            float a;
            while (!float.TryParse(Console.ReadLine(), out a) && a <= float.MaxValue && a >= float.MinValue)
                Console.Write("Некорректные данные, попробуйте еще раз: ");
            return a;
        }

        public static Matrix ReadMatrix(string path)
        {
            StreamReader reader = new StreamReader(path);
            string str = reader.ReadToEnd();
            reader.Close();
            Matrix Mat = CreateArr(str);
            string[] num = str.Split('\n');
            for (int i = 0; i < Mat.Str; i++)
            {
                string[] temp = num[i].Split(' ');
                for (int j = 0; j < temp.Length; j++)
                {
                    Mat[i, j] = Convert.ToSingle(temp[j]);
                }
            }
            return Mat;
        }

        public static Matrix Set(int m, int n)
        {
            Matrix Mat = new Matrix(m, n);
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    Console.Write("[" + i + "," + j + "]: ");
                    Mat[i, j] = CheckFloat();

                }
            }
            Console.WriteLine("Введенная матрица: ");
            Console.WriteLine(Mat);
            return Mat;
        }

        public static Matrix CreateArr(string s)
        {
            int a = 1, b = 0;
            for (int i = 0; i < s.Length; i++)
            {
                if (s[i] == '\n') a++;
                if (s[i] == ' ') b++;
            }
            Matrix arr = new Matrix(a, (b / a) + 1);
            return arr;
        }

        public static void Transpose(Matrix Mat)
        {
            Console.Clear();
            Console.WriteLine("Транспонированная матрица: ");
            for (int i = 0; i < Mat.Col; i++)
            {
                for (int j = 0; j < Mat.Str; j++)
                {
                    Console.Write("{0, 4}", Mat[j, i]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }

        public static int CheckInt()
        {
            int a;
            while (!int.TryParse(Console.ReadLine(), out a) && a <= Int32.MaxValue && a >= Int32.MinValue)
                Console.Write("Некорректные данные, попробуйте еще раз: ");
            return a;
        }

        static void MultNum(Matrix A, float x)
        {
            for (int i = 0; i < A.Str; i++)
            {
                for (int j = 0; j < A.Col; j++)
                {
                    A[i, j] *= x;
                }
            }
            Console.Clear();
            Console.WriteLine("Произведение матрицы на число " + x + ":");
            Console.WriteLine(A);
        }

        static void Addition(Matrix A)
        {
            Console.WriteLine("Введите матрицу: ");
            Matrix B = Set(A.Str, A.Col);
            for (int i = 0; i < A.Str; i++)
            {
                for (int j = 0; j < A.Col; j++)
                {
                    A[i, j] += B[i, j];
                }
            }
            Console.Clear();
            Console.WriteLine("Сумма матриц: ");
            Console.WriteLine(A);
        }

        static void MultMat(Matrix A)
        {
            Console.Write("Введите число столбцов второй матрицы: ");
            int col = CheckInt();
            Matrix B = Set(A.Col, col);
            float[][] mat = new float[B.Str][];
            for (int i = 0; i < A.Str; i++)
            {
                mat[i] = new float[B.Col];
                for (int j = 0; j < B.Col; j++)
                {
                    for (int k = 0; k < A.Col; k++)
                    {
                        mat[i][j] += A[i, k] * B[k, j];
                    }
                }
            }
            Console.Clear();
            Console.WriteLine("Произведение матриц: ");
            for (int i = 0; i < mat.GetLength(0); i++)
            {
                for (int j = 0; j < col; j++)
                {
                    Console.Write("{0, 4}", mat[i][j]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }

        static float Det(Matrix A)
        {
            float[,] copy = new float[A.Str, A.Col];
            for (int i = 0; i < A.Str; i++)
            {
                for (int j = 0; j < A.Col; j++)
                {
                    copy[i, j] = A[i, j];
                }
            }
            for (int k = 1; k < A.Str; k++)
            {
                for (int i = k; i < A.Str; i++)
                {
                    float C = copy[i, k - 1] / copy[k - 1, k - 1];
                    for (int j = 0; j < A.Str; j++)
                    {
                        copy[i, j] -= C * copy[k - 1, j];

                    }
                }
            }
            float det = 1;
            for (int i = 0; i < A.Str; i++)
            {
                det *= copy[i, i];
            }
            return det;
        }

        static Matrix Minor(Matrix A, int m, int n)
        {
            Matrix a = new Matrix(A.Str - 1, A.Col);
            int index = 0;
            for (int i = 0; i < A.Str; i++)
            {
                if (i == m)
                {
                    continue;
                }
                else
                {
                    for (int j = 0; j < A.Col; j++)
                    {
                        a[index, j] = A[i, j];
                    }
                    index++;
                }

            }
            Matrix b = new Matrix(a.Str, a.Col - 1);
            for (int i = 0; i < a.Str; i++)
            {
                for (int j = 0; j < a.Col - 1; j++)
                {
                    if (j == n)
                    {
                        for (int z = j; z < b.Col; z++)
                        {
                            b[i, z] = a[i, z + 1];
                        }
                        break;
                    }
                    else
                    {
                        b[i, j] = a[i, j];
                    }
                }
            }
            return b;
        }

        static void InverseMat(Matrix A)
        {
            if (Det(A) == 0)
            {
                Console.Clear();
                Console.WriteLine("Так как определитель равен 0 данная матрица не имеет обратной матрицы\n");
            }
            else
            {
                float d = Det(A);
                float[,] rev = new float[A.Str, A.Col];
                for (int i = 0; i < A.Str; i++)
                {
                    for (int j = 0; j < A.Col; j++)
                    {
                        Matrix temp = Minor(A, i, j);
                        rev[i, j] = Det(temp) * (float)Math.Pow(-1, i + j);
                        rev[i, j] /= d;
                    }
                }
                Console.Clear();
                Console.WriteLine("Обратная матрица: ");
                for (int i = 0; i < A.Col; i++)
                {
                    for (int j = 0; j < A.Str; j++)
                    {
                        Console.Write("{0, 12}", rev[j, i]);
                    }
                    Console.WriteLine();
                }
            }
        }

        static void Commands()
        {
            Console.WriteLine("1 - Умножение матрицы на число");
            Console.WriteLine("2 - Сложение матриц");
            Console.WriteLine("3 - Умножение матриц");
            Console.WriteLine("4 - Транспонирование");
            Console.WriteLine("5 - Найти определитель");
            Console.WriteLine("6 - Найти обратную матрицу");
            Console.WriteLine("7 - Ввести новую матрицу");
            Console.Write("Введите команду: ");
        }

        static Matrix NewMat(Matrix A)
        {
            Console.Write("Введите число строк в матрице: ");
            int m = -1;
            while (m < 0)
            {
                m = CheckInt();
            }
            Console.Write("Введите число столбцов в матрице: ");
            int n = -1;
            while (n < 1)
            {
                n = CheckInt();
            }
            Matrix B = new Matrix(m, n);
            A = B;
            Console.Clear();
            A = Set(m, n);
            return A;
        }

        static void Main(string[] args)
        {
            string path = "E:\\Рабочий стол\\C#\\LR 1(new)\\matrix.txt";
            Matrix A = ReadMatrix(path);
            Console.WriteLine("Исходная матрица: ");
            Console.WriteLine(A);
            Commands();
            int n;
            do
            {
                n = CheckInt();
                while (n < 1 || n > 7)
                {
                    Console.Write("Некорректные данные, попробуйте еще раз: ");
                    n = CheckInt();
                }
                switch (n)
                {
                    case 1:
                        Console.Write("Введите число на которое хотите умнжить: ");
                        float x = CheckFloat();
                        MultNum(A, x);
                        break;
                    case 2:
                        Addition(A);
                        break;
                    case 3:
                        MultMat(A);
                        break;
                    case 4:
                        Transpose(A);
                        break;
                    case 5:
                        Console.Clear();
                        if (A.Str != A.Col) Console.WriteLine("У этой матрицы нет определителя\n");
                        else Console.WriteLine("Определитель матрицы: " + Det(A) + "\n");
                        break;
                    case 6:
                        Console.Clear();
                        if (A.Str != A.Col) Console.WriteLine("У этой матрицы нет обратной матрицы\n");
                        else InverseMat(A);
                        break;
                    case 7:
                        A = NewMat(A);
                        break;
                }
                Commands();
            } while (n >= 1 && n <= 7);
        }
    }
}