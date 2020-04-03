using System;

namespace Models
{
    public class Error
    {
        public string Source { get; set; }

        public string Message { get; set; }

        public string StackTrace { get; set; }

        public DateTime Time { get; set; }

        public Error(string source, string message, string stackTrace,
            DateTime time)
        {
            Source = source;
            Message = message;
            StackTrace = stackTrace;
            Time = time;
        }
    }
}
