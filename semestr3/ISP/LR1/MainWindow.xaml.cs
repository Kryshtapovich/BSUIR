using Microsoft.Win32;
using System;
using System.Windows;

namespace LR1
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void BtnOpen_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog
            {
                Filter = "Текстовый файл(*.txt)|*.txt|Бинарный файл(*.bin)|*.bin"
            };
            openFile.ShowDialog();

            MyFileClass.Read(openFile.FileName, out Student student);

            textBox.Clear();
            textBox.AppendText(student?.ShowInfo());
        }

        private void BtnSave_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog
            {
                Filter = "Текстовый файл(*.txt)|*.txt|Бинарный файл(*.bin)|*.bin"
            };
            saveFile.ShowDialog();

            try
            {
                Student student = new Student
                {
                    Name = nameBox.Text,
                    Age = Convert.ToInt32(ageBox.Text),
                    University = univerBox.Text,
                    Faculty = facBox.Text,
                    Speciality = specBox.Text
                };
                MyFileClass.Write(saveFile.FileName, student);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void BtnComp_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog
            {
                Filter = "Все файлы(*.*)|*.*"
            };
            openFile.ShowDialog();

            SaveFileDialog saveFile = new SaveFileDialog
            {
                Filter = "Все файлы(*.*)|*.*"
            };
            saveFile.ShowDialog();

            MyFileClass.Compress(openFile.FileName, saveFile.FileName, out string message);
            textBox.Text = message;
        }

        private void BtnDecomp_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog
            {
                Filter = "Все файлы(*.*)|*.*"
            };
            openFile.ShowDialog();

            SaveFileDialog saveFile = new SaveFileDialog
            {
                Filter = "Все файлы(*.*)|*.*"
            };
            saveFile.ShowDialog();

            MyFileClass.Decompress(openFile.FileName, saveFile.FileName, out string message);
            textBox.Text = message;
        }
    }
}
