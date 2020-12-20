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
    ///     In a module type, mark methods or fields with this attribute to have them exposed as module functions.
    ///     Methods must have the signature "public static DynValue ...(ScriptExecutionContextCallbackArguments)".
    ///     Fields must be static or const strings, with an anonymous Lua function inside.
    ///     See <see cref="LuaModuleAttribute" /> for more information about modules.
    /// </summary>
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Field, Inherited = false)]
    public sealed class LuaModuleMethodAttribute : Attribute
    {
        /// <summary>
        ///     Gets or sets the name of the function in the module (defaults to member name)
        /// </summary>
        public string Name { get; set; }
    }
}