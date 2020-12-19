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
    ///     Lists a userdata member not to be exposed to scripts referencing it by name.
    /// </summary>
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct, AllowMultiple = true)]
    public sealed class MoonSharpHideMemberAttribute : Attribute
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="MoonSharpHideMemberAttribute" /> class.
        /// </summary>
        /// <param name="memberName">Name of the member to hide.</param>
        public MoonSharpHideMemberAttribute(string memberName)
        {
            MemberName = memberName;
        }

        /// <summary>
        ///     Gets the name of the member to be hidden.
        /// </summary>
        public string MemberName { get; }
    }
}