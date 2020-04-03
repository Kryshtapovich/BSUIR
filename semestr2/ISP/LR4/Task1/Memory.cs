using System.Runtime.InteropServices;

namespace Task1
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
    class Memory
    {
        public uint Length;
        public uint MemoryLoad;
        public ulong TotalPhys;
        public ulong AvailPhys;
        public ulong TotalPageFile;
        public ulong AvailPageFile;
        public ulong TotalVirtual;
        public ulong AvailVirtual;
        public ulong AvailExtendedVirtual;

        public Memory()
        {
            this.Length = (uint)Marshal.SizeOf(typeof(Memory));
        }
    }
}
