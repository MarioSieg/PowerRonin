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
    ///     Specifies how constructors are used when initializing objects during deserialization by the
    ///     <see cref="JsonSerializer" />.
    /// </summary>
    public enum ConstructorHandling
    {
        /// <summary>
        ///     First attempt to use the public default constructor, then fall back to a single parameterized constructor, then to
        ///     the non-public default constructor.
        /// </summary>
        Default = 0,

        /// <summary>
        ///     Json.NET will use a non-public default constructor before falling back to a parameterized constructor.
        /// </summary>
        AllowNonPublicDefaultConstructor = 1
    }
}