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

#if !HAVE_TRACE_WRITER
using Dreamcast.Json.Serialization;

namespace Dreamcast.Json
{
    /// <summary>
    ///     Specifies what messages to output for the <see cref="ITraceWriter" /> class.
    /// </summary>
    public enum TraceLevel
    {
        /// <summary>
        ///     Output no tracing and debugging messages.
        /// </summary>
        Off = 0,

        /// <summary>
        ///     Output error-handling messages.
        /// </summary>
        Error = 1,

        /// <summary>
        ///     Output warnings and error-handling messages.
        /// </summary>
        Warning = 2,

        /// <summary>
        ///     Output informational messages, warnings, and error-handling messages.
        /// </summary>
        Info = 3,

        /// <summary>
        ///     Output all debugging and tracing messages.
        /// </summary>
        Verbose = 4
    }
}

#endif