// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

using System.Runtime.CompilerServices;

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

    /// <summary>
    ///     Contains methods to write logs into the protocol,
    ///     which is displayed in the terminal and written into a log file.
    /// </summary>
    public static class Protocol
    {
        /// <summary>
        ///     Current number of warning messages in the protocol.
        /// </summary>
        public static uint WarningMessagesCount { get; private set; }

        /// <summary>
        ///     Current number of error messages in the protocol.
        /// </summary>
        public static uint ErrorMessagesCount { get; private set; }

        /// <summary>
        ///     Logs a message to the protocol.
        /// </summary>
        /// <param name="level">The log level.</param>
        /// <param name="message">The message to log.</param>
        [NativeRuntimeCall]
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Log(LogLevel level, string message);

        /// <summary>
        ///     Shorthand for Log(LogLevel.Trace, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Trace(string message)
        {
            Log(LogLevel.Trace, message);
        }

        /// <summary>
        ///     Shorthand for Log(LogLevel.Debug, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Debug(string message)
        {
            Log(LogLevel.Debug, message);
        }

        /// <summary>
        ///     Shorthand for Log(LogLevel.Info, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Info(string message)
        {
            Log(LogLevel.Info, message);
        }

        /// <summary>
        ///     Shorthand for Log(LogLevel.Warn, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Warn(string message)
        {
            Log(LogLevel.Warn, message);
            ++WarningMessagesCount;
        }

        /// <summary>
        ///     Shorthand for Log(LogLevel.Error, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Error(string message)
        {
            Log(LogLevel.Error, message);
            ++ErrorMessagesCount;
        }

        /// <summary>
        ///     Shorthand for Log(LogLevel.Critical, message);
        /// </summary>
        /// <param name="message">The message to log.</param>
        public static void Critical(string message)
        {
            Log(LogLevel.Critical, message);
        }

        /// <summary>
        ///     Inserts a separator (64 * -) into the protocol.
        /// </summary>
        public static void Separator()
        {
            Info("----------------------------------------------------------------");
        }

        /// <summary>
        ///     Flushes the protocol into a log file.
        /// </summary>
        [NativeRuntimeCall]
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Flush();

        /// <summary>
        ///     Sets the formatting pattern of the protocol scripting formatter.
        /// </summary>
        /// <param name="pattern"></param>
        [NativeRuntimeCall]
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetFormatPattern(string pattern);
    }
}