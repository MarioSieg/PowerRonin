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
    ///     In a module type, mark fields with this attribute to have them exposed as a module constant.
    ///     See <see cref="MoonSharpModuleAttribute" /> for more information about modules.
    /// </summary>
    [AttributeUsage(AttributeTargets.Field)]
    public sealed class MoonSharpModuleConstantAttribute : Attribute
    {
        /// <summary>
        ///     Gets or sets the name of the constant - if different from the name of the field itself
        /// </summary>
        public string Name { get; set; }
    }
}