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

namespace Dreamcast.Json
{
    /// <summary>
    ///     Specifies reference handling options for the <see cref="JsonSerializer" />.
    ///     Note that references cannot be preserved when a value is set via a non-default constructor such as types that
    ///     implement <see cref="T:System.Runtime.Serialization.ISerializable" />.
    /// </summary>
    /// <example>
    ///     <code lang="cs" source="..\Src\Dreamcast.Json.Tests\Documentation\SerializationTests.cs"
    ///         region="PreservingObjectReferencesOn" title="Preserve Object References" />
    /// </example>
    [Flags]
    public enum PreserveReferencesHandling
    {
        /// <summary>
        ///     Do not preserve references when serializing types.
        /// </summary>
        None = 0,

        /// <summary>
        ///     Preserve references when serializing into a JSON object structure.
        /// </summary>
        Objects = 1,

        /// <summary>
        ///     Preserve references when serializing into a JSON array structure.
        /// </summary>
        Arrays = 2,

        /// <summary>
        ///     Preserve references when serializing.
        /// </summary>
        All = Objects | Arrays
    }
}