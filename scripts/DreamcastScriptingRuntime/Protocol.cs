using System.Runtime.CompilerServices;

namespace Dreamcast
{
    /// <summary>
    /// Contains all log levels.
    /// </summary>
    public enum LogLevel : byte
    {
        /// <summary>
        /// Trace log.
        /// </summary>
        Trace = 0,

        /// <summary>
        /// Debug log.
        /// </summary>
        Debug = 1,

        /// <summary>
        /// Info log.
        /// </summary>
        Info = 2,

        /// <summary>
        /// Warning log.
        /// </summary>
        Warn = 3,

        /// <summary>
        /// Error log.
        /// </summary>
        Error = 4,

        /// <summary>
        /// Criticial.
        /// </summary>
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
        public static void Log(LogLevel level, string message)
        {
            __Log((byte)level, message);
        }

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
        public static void Separator()
        {
            Info("----------------------------------------------------------------");
        }

        /// <summary>
        /// Flushes the protocol into a log file.
        /// </summary>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Flush();


        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetFormatPattern(string patter);


        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void __Log(byte level, string message);
    }
}
