using System;
using System.Collections.Generic;
using System.Linq;

namespace Task13
{
    class Program
    {
        static int[] ParseString(string str) => str.Split().Select(x => int.Parse(x)).ToArray();

        static List<int>[] EnterGraph(int apexNum, int ribNum)
        {
            List<int>[] graph = new List<int>[apexNum];
            for (int i = 0; i < apexNum; i++)
            {
                graph[i] = new List<int>();
            }

            for (int i = 0; i < ribNum; i++)
            {
                var rib = ParseString(Console.ReadLine());
                graph[--rib[0]].Add(--rib[1]);
                graph[rib[1]].Add(rib[0]);
            }
            return graph;
        }

        static void DeleteRibs(List<int>[] graph, int apexNum, int ribNum)
        {
            int res = 0;
            Del delete = null;
            delete = (int i, bool[] v, List<int>[] g) =>
            {
                v[i] = true;
                foreach (var elem in g[i])
                {
                    if (!v[elem])
                    {
                        delete(elem, v, g);
                    }
                }
            };

            bool[] isVisited = new bool[apexNum];
            for (int i = 0; i < apexNum; i++)
            {
                if (!isVisited[i])
                {
                    delete(i, isVisited, graph);
                    res++;
                }
            }
            Console.WriteLine((ribNum - apexNum + 1 >= 0 && res == 1) ? ribNum - apexNum + 1 : -1);
        }

        delegate void Del(int index, bool[] isVisited, List<int>[] graph);
        static void Main(string[] args)
        {
            var parameters = ParseString(Console.ReadLine());
            int apexNum = parameters[0];
            int ribNum = parameters[1];
            var graph = EnterGraph(apexNum, ribNum);
            DeleteRibs(graph, apexNum, ribNum);
        }
    }
}
