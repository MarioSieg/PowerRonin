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
    ///     Enumeration of the possible performance counters
    /// </summary>
    public enum PerformanceCounter
    {
        /// <summary>
        ///     Measures the time spent parsing the source creating the AST
        /// </summary>
        AstCreation,

        /// <summary>
        ///     Measures the time spent converting ASTs in bytecode
        /// </summary>
        Compilation,

        /// <summary>
        ///     Measures the time spent in executing scripts
        /// </summary>
        Execution,

        /// <summary>
        ///     Measures the on the fly creation/compilation of functions in userdata descriptors
        /// </summary>
        AdaptersCompilation,

        /// <summary>
        ///     Sentinel value to get the enum size
        /// </summary>
        LastValue
    }
}