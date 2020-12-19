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

namespace MoonSharp.Interpreter.Diagnostics
{
    /// <summary>
    ///     Enumeration of unit of measures of the performance counters
    /// </summary>
    public enum PerformanceCounterType
    {
        /// <summary>
        ///     The performance counter is specified in bytes (of memory)
        /// </summary>
        MemoryBytes,

        /// <summary>
        ///     The performance counter is specified in milliseconds
        /// </summary>
        TimeMilliseconds
    }
}