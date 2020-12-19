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

namespace Dreamcast.Lua.Interpreter
{
    /// <summary>
    ///     Enumeration of the types of SymbolRef
    /// </summary>
    public enum SymbolRefType
    {
        /// <summary>
        ///     The symbol ref of a local variable
        /// </summary>
        Local,

        /// <summary>
        ///     The symbol ref of an upvalue variable
        /// </summary>
        Upvalue,

        /// <summary>
        ///     The symbol ref of a global variable
        /// </summary>
        Global,

        /// <summary>
        ///     The symbol ref of the global environment
        /// </summary>
        DefaultEnv
    }
}