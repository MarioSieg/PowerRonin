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
    ///     Specifies missing member handling options for the <see cref="JsonSerializer" />.
    /// </summary>
    public enum MissingMemberHandling
    {
        /// <summary>
        ///     Ignore a missing member and do not attempt to deserialize it.
        /// </summary>
        Ignore = 0,

        /// <summary>
        ///     Throw a <see cref="JsonSerializationException" /> when a missing member is encountered during deserialization.
        /// </summary>
        Error = 1
    }
}