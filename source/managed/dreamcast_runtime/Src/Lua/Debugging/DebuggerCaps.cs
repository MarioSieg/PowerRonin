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

using System;

namespace Dreamcast.Lua.Interpreter.Debugging
{
    /// <summary>
    ///     Enumeration of capabilities for a debugger
    /// </summary>
    [Flags]
    public enum DebuggerCaps
    {
        /// <summary>
        ///     Flag set if the debugger can debug source code
        /// </summary>
        CanDebugSourceCode = 0x1,

        /// <summary>
        ///     Flag set if the can debug VM bytecode
        /// </summary>
        CanDebugByteCode = 0x2,

        /// <summary>
        ///     Flag set if the debugger uses breakpoints based on lines instead of tokens
        /// </summary>
        HasLineBasedBreakpoints = 0x4
    }
}