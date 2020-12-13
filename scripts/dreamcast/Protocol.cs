using System.Runtime.CompilerServices;

namespace dreamcast
{
    /// <summary>
    /// Contains all log levels.
    /// </summary>
    public enum LogLevel : byte
    {
        Trace = 0,
        Debug = 1,
        Info = 2,
        Warn = 3,
        Error = 4,
        Critical = 5,
    }

    /// <summary>
    /// Contains methods to write logs into the protocol,
    /// which is displayed in the terminal and written into a log file.
    /// </summary>
    public static class Protocol
    {
        /// <summary>
        /// Current number of warning messages in the protocol.
        /// </summary>
        public static uint WarningMessagesCount { get; private set; }

        /// <summary>
        /// Current number of error messages in the protocol.
        /// </summary>
        public static uint ErrorMessagesCount { get; private set; }

        /// <summary>
        /// Logs a message to the protocol.
        /// </summary>
        /// <param name="level">The log level.</param>
        /// <param name="message">The message to log.</param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Log(LogLevel level, string message);

        /// <summary>
        /// Shorthand for Log(LogLevel.Trace, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Trace(string message)
        {
            Log(LogLevel.Trace, message);
        }

        /// <summary>
        /// Shorthand for Log(LogLevel.Debug, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Debug(string message)
        {
            Log(LogLevel.Debug, message);
        }

        /// <summary>
        /// Shorthand for Log(LogLevel.Info, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Info(string message)
        {
            Log(LogLevel.Info, message);
        }

        /// <summary>
        /// Shorthand for Log(LogLevel.Warn, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Warn(string message)
        {
            Log(LogLevel.Warn, message);
            ++WarningMessagesCount;
        }

        /// <summary>
        /// Shorthand for Log(LogLevel.Error, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Error(string message)
        {
            Log(LogLevel.Error, message);
            ++ErrorMessagesCount;
        }

        /// <summary>
        /// Shorthand for Log(LogLevel.Critical, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Critical(string message)
        {
            Log(LogLevel.Critical, message);
        }

        /// <summary>
        /// Inserts a separator (64 * -) into the protocol.
        /// </summary>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Separator();
    }
}
