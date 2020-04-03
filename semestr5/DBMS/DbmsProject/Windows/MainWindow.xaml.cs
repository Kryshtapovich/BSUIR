using DbmsProject.Contexts;
using DbmsProject.Models;
using System;
using System.ComponentModel;
using System.Windows;

namespace DbmsProject
{
    public partial class MainWindow : Window
    {
        private readonly ApplicationContext context;
        private bool openNew;

        public MainWindow()
        {
            InitializeComponent();
            context = new ApplicationContext();
        }

        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                openNew = true;
                context.Authorize(Login.Text, Password.Text);
                Close();
            }
            catch (NullReferenceException ex)
            {
                Error.Content = ex.Message;
            }
        }

        private void RegisterButton_Click(object sender, RoutedEventArgs e)
        {
            openNew = true;
            var user = new Account
            {
                FirstName = FirstName.Text,
                LastName = LastName.Text,
                Email = RegisterEmail.Text
            };
            context.Register(user, RegisterPassword.Text);
            Close();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            if (openNew)
            {
                Window window = context.User.Role == Role.USER ? new UserWindow(context) : new AdminWindow(context);
                window.Show();
                openNew = false;
            }
        }
    }
}
