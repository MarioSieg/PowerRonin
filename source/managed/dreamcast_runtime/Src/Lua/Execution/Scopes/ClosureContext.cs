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
using System.Linq;

namespace MoonSharp.Interpreter.Execution
{
    /// <summary>
    ///     The scope of a closure (container of upvalues)
    /// </summary>
    internal class ClosureContext : List<DynValue>
    {
        internal ClosureContext(SymbolRef[] symbols, IEnumerable<DynValue> values)
        {
            Symbols = symbols.Select(s => s.i_Name).ToArray();
            AddRange(values);
        }

        internal ClosureContext()
        {
            Symbols = new string[0];
        }

        /// <summary>
        ///     Gets the symbols.
        /// </summary>
        public string[] Symbols { get; }
    }
}