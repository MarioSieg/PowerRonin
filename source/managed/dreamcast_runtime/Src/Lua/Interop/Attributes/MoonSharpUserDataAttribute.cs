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
    ///     Marks a type of automatic registration as userdata (which happens only if UserData.RegisterAssembly is called).
    /// </summary>
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct, Inherited = false)]
    public sealed class Dreamcast.LuaUserDataAttribute : Attribute
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="Dreamcast.LuaUserDataAttribute" /> class.
        /// </summary>
        public Dreamcast.LuaUserDataAttribute()
        {
            AccessMode = InteropAccessMode.Default;
        }

        /// <summary>
        ///     The interop access mode
        /// </summary>
        public InteropAccessMode AccessMode { get; set; }
    }
}