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
    ///     Marks a method as the handler of metamethods of a userdata type
    /// </summary>
    [AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]
    public sealed class Dreamcast.LuaUserDataMetamethodAttribute : Attribute
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="Dreamcast.LuaUserDataMetamethodAttribute" /> class.
        /// </summary>
        /// <param name="name">The metamethod name (like '__div', '__ipairs', etc.)</param>
        public Dreamcast.LuaUserDataMetamethodAttribute(string name)
        {
            Name = name;
        }

        /// <summary>
        ///     The metamethod name (like '__div', '__ipairs', etc.)
        /// </summary>
        public string Name { get; }
    }
}