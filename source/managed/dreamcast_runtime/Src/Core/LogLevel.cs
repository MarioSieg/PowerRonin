namespace Dreamcast.Core
{
    /// <summary>
    ///     Contains all log levels.
    /// </summary>
    public enum LogLevel : byte
    {
        /// <summary>
        ///     Trace log.
        /// </summary>
        Trace = 0,

        /// <summary>
        ///     Debug log.
        /// </summary>
        Debug = 1,

        /// <summary>
        ///     Info log.
        /// </summary>
        Info = 2,

        /// <summary>
        ///     Warning log.
        /// </summary>
        Warn = 3,

        /// <summary>
        ///     Error log.
        /// </summary>
        Error = 4,

        /// <summary>
        ///     Criticial.
        /// </summary>
        Critical = 5
    }
}