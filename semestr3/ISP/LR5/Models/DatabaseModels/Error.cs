using System;

namespace Models
{
    public class Error
    {
        public string Source { get; private set; }

        public string Message { get; private set; }

        public string StackTrace { get; private set; }

        public DateTime Time { get; private set; }

        public Error(string message, string source,
            string stackTrace, DateTime time)
        {
            Source = source;
            Message = message;
            StackTrace = stackTrace;
            Time = time;
        }
    }
}
