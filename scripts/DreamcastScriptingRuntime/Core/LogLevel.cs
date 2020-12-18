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