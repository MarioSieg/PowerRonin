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
    ///     Specifies how object creation is handled by the <see cref="JsonSerializer" />.
    /// </summary>
    public enum ObjectCreationHandling
    {
        /// <summary>
        ///     Reuse existing objects, create new objects when needed.
        /// </summary>
        Auto = 0,

        /// <summary>
        ///     Only reuse existing objects.
        /// </summary>
        Reuse = 1,

        /// <summary>
        ///     Always create new objects.
        /// </summary>
        Replace = 2
    }
}