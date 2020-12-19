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

namespace Dreamcast.Lua.Interpreter
{
    /// <summary>
    ///     Marks a CLR type to be a Dreamcast.Lua module.
    ///     Modules are the fastest way to bring interop between scripts and CLR code, albeit at the cost of a very increased
    ///     complexity in writing them. Modules is what's used for the standard library, for maximum efficiency.
    ///     Modules are basically classes containing only static methods, with the callback function signature.
    ///     See <see cref="Table" /> and <see cref="ModuleRegister" /> for (extension) methods used to register modules to a
    ///     table.
    ///     See <see cref="CallbackFunction" /> for information regarding the standard callback signature along with easier
    ///     ways
    ///     to marshal methods.
    ///     See <see cref="UserData" /> for easier object marshalling.
    /// </summary>
    [AttributeUsage(AttributeTargets.Class, Inherited = false)]
    public sealed class Dreamcast.LuaModuleAttribute : Attribute
    {
        /// <summary>
        ///     Gets or sets the namespace, that is the name of the table which will contain the defined functions.
        ///     Can be null to be in the global table.
        /// </summary>
        public string Namespace { get; set; }
    }
}