using System;
using System.Text;
using System.Runtime.InteropServices;

namespace Task1
{
    class Disc
    {
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern bool GetDiskFreeSpaceEx(string lpDirectoryName, out ulong lpFreeBytesAvailable, out ulong lpTotalNumberOfBytes, out ulong lpTotalNumberOfFreeBytes);
        public static string Info(string disc)
        {
            ulong FreeBytesAvailable;
            ulong TotalNumberOfBytes;
            ulong TotalNumberOfFreeBytes;

            bool success = GetDiskFreeSpaceEx(disc, out FreeBytesAvailable, out TotalNumberOfBytes, out TotalNumberOfFreeBytes);

            StringBuilder str = new StringBuilder();
            str.Append($"Free Space on disc {disc} {(FreeBytesAvailable / Math.Pow(2, 30)).ToString()}" + " GB\n");
            str.Append($"Total Space on disc {disc} {(TotalNumberOfBytes / Math.Pow(2, 30)).ToString()}" + " GB\n");
            return str.ToString();
        }
    }
}
