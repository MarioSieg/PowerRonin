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
    ///     Specifies metadata property handling options for the <see cref="JsonSerializer" />.
    /// </summary>
    public enum MetadataPropertyHandling
    {
        /// <summary>
        ///     Read metadata properties located at the start of a JSON object.
        /// </summary>
        Default = 0,

        /// <summary>
        ///     Read metadata properties located anywhere in a JSON object. Note that this setting will impact performance.
        /// </summary>
        ReadAhead = 1,

        /// <summary>
        ///     Do not try to read metadata properties.
        /// </summary>
        Ignore = 2
    }
}