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

using System.Collections.Generic;
using MoonSharp.Interpreter.Execution.VM;

namespace MoonSharp.Interpreter.Debugging
{
    /// <summary>
    ///     Class providing services specific to debugger implementations.
    /// </summary>
    /// <seealso cref="MoonSharp.Interpreter.IScriptPrivateResource" />
    public sealed class DebugService : IScriptPrivateResource
    {
        private readonly Processor m_Processor;

        internal DebugService(Script script, Processor processor)
        {
            OwnerScript = script;
            m_Processor = processor;
        }

        /// <summary>
        ///     Gets the script owning this resource.
        /// </summary>
        /// <value>
        ///     The script owning this resource.
        /// </value>
        public Script OwnerScript { get; }

        /// <summary>
        ///     Resets the break points for a given file. Supports only line-based breakpoints.
        /// </summary>
        /// <param name="src">The source.</param>
        /// <param name="lines">The lines.</param>
        /// <returns>The lines for which breakpoints have been set</returns>
        public HashSet<int> ResetBreakPoints(SourceCode src, HashSet<int> lines)
        {
            return m_Processor.ResetBreakPoints(src, lines);
        }
    }
}