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
    ///     Flags to alter the way the DynValue.CheckType and other related functions operate on data types for
    ///     validation.
    /// </summary>
    [Flags]
    public enum TypeValidationFlags
    {
        /// <summary>
        ///     No type validation specific behaviour
        /// </summary>
        None = 0,

        /// <summary>
        ///     Nil and Void values are allowed (and returned by the call)
        /// </summary>
        AllowNil = 0x1,

        /// <summary>
        ///     Simple autoconversions are attempted:
        ///     1) Numbers are convertible to strings
        ///     2) Strings are convertible to numbers if they contain a number
        ///     3) Everything is convertible to boolean (with void and nil converting to 'false', everything else converting to
        ///     'true')
        ///     Note: if both AutoConvert and AllowNil are specified, nils will NOT be converted to false booleans.
        /// </summary>
        AutoConvert = 0x2,

        /// <summary>
        ///     The default : Autoconverting values, no nils.
        /// </summary>
        Default = AutoConvert
    }
}