using System;
using System.Collections.Generic;
using System.Linq;

namespace Task5
{
    class Program
    {
        static int[] ParseString(string str) => str.Split().Select(x => int.Parse(x)).ToArray();

        static List<int[]>[] EnterGraph(int apexNum, int ribNum)
        {
            List<int[]>[] graph = new List<int[]>[apexNum];

            for (int i = 0; i < apexNum; i++)
            {
                graph[i] = new List<int[]>();
            }

            for (int i = 0; i < ribNum; i++)
            {
                var rib = ParseString(Console.ReadLine());
                graph[--rib[0]].Add(new int[] { --rib[1], rib[2] });
                graph[rib[1]].Add(new int[] { rib[0], rib[2] });
            }

            return graph;
        }

        static void Main(string[] args)
        {
            int apexNum = int.Parse(Console.ReadLine());
            int ribNum = int.Parse(Console.ReadLine());
            var graph = EnterGraph(apexNum, ribNum);
            int start = int.Parse(Console.ReadLine()) - 1;
            int end = int.Parse(Console.ReadLine()) - 1;
            Dijkstra(graph, apexNum, start, end);
        }

        static void Dijkstra(List<int[]>[] graph, int apexNum, int start, int end)
        {
            long[] weights = new long[apexNum];
            for (int i = 0; i < weights.Length; i++)
            {
                weights[i] = long.MaxValue;
            }
            weights[start] = 0;

            bool[] isVisited = new bool[apexNum];

            for (int i = 0; i < apexNum; i++)
            {
                int currApex = -1;

                for (int j = 0; j < apexNum; j++)
                {
                    if (!isVisited[j])
                    {
                        if (currApex == -1)
                        {
                            currApex = j;
                        }
                        else if (weights[j] < weights[currApex])
                        {
                            currApex = j;
                        }
                    }
                }
                isVisited[currApex] = true;
                Visit(graph, currApex, ref weights);
            }
            Console.WriteLine(weights[end]);
        }

        static void Visit(List<int[]>[] graph, int currApex, ref long[] weights)
        {
            for (int i = 0; i < graph[currApex].Count; i++)
            {
                int neighbour = graph[currApex][i][0];
                int weight = graph[currApex][i][1];

                long path = weights[currApex] + weight;
                if (path < weights[neighbour])
                {
                    weights[neighbour] = path;
                }
            }
        }
    }
}
