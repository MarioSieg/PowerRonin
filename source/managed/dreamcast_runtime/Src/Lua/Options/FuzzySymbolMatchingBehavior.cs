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

namespace MoonSharp.Interpreter
{
    /// <summary>
    ///     A flag that controls if/how symbols (method, property, userdata) are fuzzily matched when they do not exist. Flags
    ///     can be combined for multiple checks.
    /// </summary>
    [Flags]
    public enum FuzzySymbolMatchingBehavior
    {
        /// <summary>No fuzzy matching is performed.</summary>
        None = 0,

        /// <summary>
        ///     The first letter of a symbol will be uppercased (to check for common C# naming conventions). For example,
        ///     testMethod() becomes TestMethod()
        /// </summary>
        UpperFirstLetter = 1,

        /// <summary>Underscores in symbols are converted to camelcase. For example, test_method() becomes testMethod()</summary>
        Camelify = 2,

        /// <summary>
        ///     Converts a symbol to pascal case. For example, test_Method_two() becomes TestMethodTwo()
        /// </summary>
        PascalCase = 4
    }
}