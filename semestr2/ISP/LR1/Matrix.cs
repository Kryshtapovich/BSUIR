namespace LR1
{
    class Matrix
    {
        private float[,] Mat;

        public Matrix(int m, int n)
        {
            Mat = new float[m, n];
        }

        public float this[int i, int j]
        {
            get
            {
                return Mat[i, j];
            }
            set
            {
                Mat[i, j] = value;
            }
        }

        public override string ToString()
        {
            string str = "";
            for (int i = 0; i < this.Str; i++)
            {
                for (int j = 0; j < this.Col; j++)
                {
                    str += Mat[i, j] + "\t";
                }
                str += "\n";
            }
            return str;
        }

        public int Str => Mat.GetLength(0);

        public int Col => Mat.GetLength(1);
    }
}
