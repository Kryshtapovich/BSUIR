using System;
using System.Collections.Generic;
using System.Linq;

namespace Task4
{
    class Field
    {
        private readonly int length;
        private readonly int width;
        private readonly int[] moveX = new int[] { 2, 2, 1, 1, -1, -1, -2, -2 };
        private readonly int[] moveY = new int[] { 1, -1, 2, -2, 2, -2, 1, -1 };
        private readonly List<int[]> steps;
        private readonly bool[,] isVisited;

        public Field(int n, int m)
        {
            length = n - 1;
            width = m - 1;
            steps = new List<int[]>();
            isVisited = new bool[n, m];
        }

        public string Traverse(int i, int j)
        {
            int result = -1;
            steps.Add(new int[] { 0, 0, 0 });
            while (steps.Count != 0)
            {
                var node = steps[0];
                steps.RemoveAt(0);
                if (node[0] == i && node[1] == j)
                {
                    result = node[2];
                    break;
                }

                if (!isVisited[node[0], node[1]])
                {
                    isVisited[node[0], node[1]] = true;
                    for (int k = 0; k < 8; k++)
                    {
                        if (Check(node[0] + moveX[k], node[1] + moveY[k]))
                        {
                            steps.Add(new int[] { node[0] + moveX[k], node[1] + moveY[k], node[2] + 1 });
                        }
                    }
                }
            }

            return result == -1 ? "NEVAR" : result.ToString();
        }

        private bool Check(int x, int y) => x <= length && x >= 0 && y <= width && y >= 0;
    }

    class Program
    {
        static int[] ParseString(string str) => str.Split().Select(x => int.Parse(x)).ToArray();

        static void ReadParameters(out int n, out int m, out int i, out int j)
        {
            var parameters = ParseString(Console.ReadLine());
            n = parameters[0];
            m = parameters[1];
            i = --parameters[2];
            j = --parameters[3];
        }

        static void Main(string[] args)
        {
            int n, m, i, j;
            ReadParameters(out n, out m, out i, out j);
            Field field = new Field(n, m);
            Console.WriteLine(field.Traverse(i, j));
        }
    }
}
