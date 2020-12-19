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

namespace MoonSharp.Interpreter
{
    /// <summary>
    ///     State of coroutines
    /// </summary>
    public enum CoroutineState
    {
        /// <summary>
        ///     This is the main coroutine
        /// </summary>
        Main,

        /// <summary>
        ///     Coroutine has not started yet
        /// </summary>
        NotStarted,

        /// <summary>
        ///     Coroutine is suspended
        /// </summary>
        Suspended,

        /// <summary>
        ///     Coroutine has been forcefully suspended (i.e. auto-yielded)
        /// </summary>
        ForceSuspended,

        /// <summary>
        ///     Coroutine is running
        /// </summary>
        Running,

        /// <summary>
        ///     Coroutine has terminated
        /// </summary>
        Dead
    }
}