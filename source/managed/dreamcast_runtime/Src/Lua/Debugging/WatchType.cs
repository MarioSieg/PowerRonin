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

namespace MoonSharp.Interpreter.Debugging
{
    /// <summary>
    ///     Enumeration of the possible watch types
    /// </summary>
    public enum WatchType
    {
        /// <summary>
        ///     A real variable watch
        /// </summary>
        Watches,

        /// <summary>
        ///     The status of the v-stack
        /// </summary>
        VStack,

        /// <summary>
        ///     The call stack
        /// </summary>
        CallStack,

        /// <summary>
        ///     The list of coroutines
        /// </summary>
        Coroutines,

        /// <summary>
        ///     Topmost local variables
        /// </summary>
        Locals,

        /// <summary>
        ///     The list of currently active coroutines
        /// </summary>
        Threads,

        /// <summary>
        ///     The maximum value of this enum
        /// </summary>
        MaxValue
    }
}