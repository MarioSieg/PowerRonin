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

namespace Dreamcast.Json.Linq
{
    /// <summary>
    ///     Specifies how JSON arrays are merged together.
    /// </summary>
    public enum MergeArrayHandling
    {
        /// <summary>Concatenate arrays.</summary>
        Concat = 0,

        /// <summary>Union arrays, skipping items that already exist.</summary>
        Union = 1,

        /// <summary>Replace all array items.</summary>
        Replace = 2,

        /// <summary>Merge array items together, matched by index.</summary>
        Merge = 3
    }
}