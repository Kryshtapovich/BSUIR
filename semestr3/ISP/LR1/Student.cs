using System;

namespace LR1
{
    [Serializable]
    public class Student
    {
        private string name;

        private int age;

        private string university;

        private string faculty;

        private string speciality;

        public string Name
        {
            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    throw new ArgumentException("Входная строка имела неверный формат");
                }
                else
                {
                    name = value;
                }
            }
            get
            {
                return name;
            }
        }

        public int Age
        {
            set
            {
                if (value < 16)
                {
                    throw new Exception("Возраст не может быть меньше 16");
                }
                else
                {
                    age = value;
                }
            }
            get
            {
                return age;
            }
        }

        public string University
        {
            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    throw new Exception("Входная строка имела неверный формат");
                }
                else
                {
                    university = value;
                }
            }
            get
            {
                return university;
            }
        }

        public string Faculty
        {
            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    throw new Exception("Входная строка имела неверный формат");
                }
                else
                {
                    faculty = value;
                }
            }
            get
            {
                return faculty;
            }
        }

        public string Speciality
        {
            set
            {
                if (string.IsNullOrEmpty(value))
                {
                    throw new Exception("Входная строка имела неверный формат");
                }
                else
                {
                    speciality = value;
                }
            }
            get
            {
                return speciality;
            }
        }
    
        public string ShowInfo()
        {
            return $"Имя: {Name}\n" +
                   $"Возраст: {Age}\n" +
                   $"Университет: {University}\n" +
                   $"Факультет: {Faculty}\n" +
                   $"Специальность: {Speciality}";
        }
    }
}
