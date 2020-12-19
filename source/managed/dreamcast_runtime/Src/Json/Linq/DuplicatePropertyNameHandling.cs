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
    ///     Specifies how duplicate property names are handled when loading JSON.
    /// </summary>
    public enum DuplicatePropertyNameHandling
    {
        /// <summary>
        ///     Replace the existing value when there is a duplicate property. The value of the last property in the JSON object
        ///     will be used.
        /// </summary>
        Replace = 0,

        /// <summary>
        ///     Ignore the new value when there is a duplicate property. The value of the first property in the JSON object will be
        ///     used.
        /// </summary>
        Ignore = 1,

        /// <summary>
        ///     Throw a <see cref="JsonReaderException" /> when a duplicate property is encountered.
        /// </summary>
        Error = 2
    }
}