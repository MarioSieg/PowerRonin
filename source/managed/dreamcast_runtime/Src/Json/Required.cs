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
    ///     Indicating whether a property is required.
    /// </summary>
    public enum Required
    {
        /// <summary>
        ///     The property is not required. The default state.
        /// </summary>
        Default = 0,

        /// <summary>
        ///     The property must be defined in JSON but can be a null value.
        /// </summary>
        AllowNull = 1,

        /// <summary>
        ///     The property must be defined in JSON and cannot be a null value.
        /// </summary>
        Always = 2,

        /// <summary>
        ///     The property is not required but it cannot be a null value.
        /// </summary>
        DisallowNull = 3
    }
}