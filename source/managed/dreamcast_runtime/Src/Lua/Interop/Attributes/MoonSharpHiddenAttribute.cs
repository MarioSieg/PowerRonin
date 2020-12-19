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
    ///     Forces a class member visibility to scripts. Can be used to hide public members. Equivalent to
    ///     MoonSharpVisible(false).
    /// </summary>
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property | AttributeTargets.Field
                    | AttributeTargets.Constructor | AttributeTargets.Event)]
    public sealed class MoonSharpHiddenAttribute : Attribute
    {
    }
}