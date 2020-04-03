using System;
using System.Collections.Generic;
using System.Linq;

namespace Task1
{
	class Graph
    {
        private List<List<int>> Apexes;

        private bool[] isVisited;

        public Graph(int n)
        {
            Apexes = new List<List<int>>();
            for (int i = 0; i < n; i++)
            {
                Apexes.Add(new List<int>());
            }
            isVisited = new bool[n];
        }

        public void Add(int apex, int neighbour)
        {
            Apexes[apex].Add(neighbour);
            Apexes[neighbour].Add(apex);
        }

        private void Mark(int index)
        {
            isVisited[index] = true;
            foreach (var apex in Apexes[index])
            {
                if (!isVisited[apex])
                {
                    Mark(apex);
                }
            }
        }

        public int GetComponentsNumber()
        {
            int components = 0;

            for (int i = 0; i < isVisited.Length; i++)
            {
                if (!isVisited[i])
                {
                    components++;
                    Mark(i);
                }
            }

            return components;
        }
    }


    class Program
    {
        static int[] ParseString(string str)
        {
            return str.Split().Select(x => int.Parse(x)).ToArray();
        }

        static void Main(string[] args)
        {
            var parameters = ParseString(Console.ReadLine());
            int n = parameters[0];
            int m = parameters[1];

            Graph graph = new Graph(n);
            for (int i = 0; i < m; i++)
            {
                var rib = ParseString(Console.ReadLine());
                graph.Add(--rib[0], --rib[1]);
            }

            int ribsToAdd = graph.GetComponentsNumber() - 1;
            Console.WriteLine(ribsToAdd);
        }
    }
}