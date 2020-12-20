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

namespace Dreamcast.Lua.Interpreter.Interop
{
    /// <summary>
    ///     Forces a class member visibility to scripts. Can be used to hide public members or to expose non-public ones.
    /// </summary>
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property | AttributeTargets.Field
                    | AttributeTargets.Constructor | AttributeTargets.Event)]
    public sealed class LuaVisibleAttribute : Attribute
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="LuaVisibleAttribute" /> class.
        /// </summary>
        /// <param name="visible">if set to true the member will be exposed to scripts, if false the member will be hidden.</param>
        public LuaVisibleAttribute(bool visible)
        {
            Visible = visible;
        }

        /// <summary>
        ///     Gets a value indicating whether this <see cref="LuaVisibleAttribute" /> is set to "visible".
        /// </summary>
        public bool Visible { get; }
    }
}