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

namespace Dreamcast.Json
{
    /// <summary>
    ///     Specifies formatting options for the <see cref="JsonTextWriter" />.
    /// </summary>
    public enum Formatting
    {
        /// <summary>
        ///     No special formatting is applied. This is the default.
        /// </summary>
        None = 0,

        /// <summary>
        ///     Causes child objects to be indented according to the <see cref="JsonTextWriter.Indentation" /> and
        ///     <see cref="JsonTextWriter.IndentChar" /> settings.
        /// </summary>
        Indented = 1
    }
}