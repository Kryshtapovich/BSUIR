using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Task1
{
    static class SystemInfo
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern bool GlobalMemoryStatusEx(Memory info);

        [DllImport("kernel32.dll", SetLastError = false)]
        public static extern void GetSystemInfo(Processor info);

        public static string Memory()
        {
            Memory info = new Memory();
            GlobalMemoryStatusEx(info);

            StringBuilder str = new StringBuilder();
            str.Append("Memory architecture: " + info.Length.ToString() + " bit\n");
            str.Append("Memory Load: " + info.MemoryLoad.ToString() + "%" + "\n");
            str.Append("Total Memory: " + (info.TotalPhys / Math.Pow(2, 30)).ToString() + " " + "GB" + "\n");
            str.Append("Available Memory: " + (info.AvailPhys / Math.Pow(2, 30)).ToString() + " " + "GB" + "\n");
            return str.ToString();
        }

        public static string Processor()
        {
            Processor info = new Processor();
            GetSystemInfo(info);

            StringBuilder str = new StringBuilder("Proccesor architecture: ");
            switch (info.ProcessorArchitecture)
            {
                case 0:
                    str.Append("x64\n");
                    break;
                case 9:
                    str.Append("x86\n");
                    break;
                default:
                    str.Append("others\n");
                    break;
            }
            str.Append("Count of Processors: " + (info.NumberOfProcessors + 1) + "\n");
            return str.ToString();
        }
    }
}
