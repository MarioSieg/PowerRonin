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
    ///     Marks a property as a configruation property
    /// </summary>
    [AttributeUsage(AttributeTargets.Property, AllowMultiple = true)]
    public sealed class MoonSharpPropertyAttribute : Attribute
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="MoonSharpPropertyAttribute" /> class.
        /// </summary>
        public MoonSharpPropertyAttribute()
        {
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="MoonSharpPropertyAttribute" /> class.
        /// </summary>
        /// <param name="name">The name for this property</param>
        public MoonSharpPropertyAttribute(string name)
        {
            Name = name;
        }

        /// <summary>
        ///     The metamethod name (like '__div', '__ipairs', etc.)
        /// </summary>
        public string Name { get; }
    }
}