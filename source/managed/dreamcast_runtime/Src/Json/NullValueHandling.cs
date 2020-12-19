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
    ///     Specifies null value handling options for the <see cref="JsonSerializer" />.
    /// </summary>
    /// <example>
    ///     <code lang="cs" source="..\Src\Dreamcast.Json.Tests\Documentation\SerializationTests.cs"
    ///         region="ReducingSerializedJsonSizeNullValueHandlingObject" title="NullValueHandling Class" />
    ///     <code lang="cs" source="..\Src\Dreamcast.Json.Tests\Documentation\SerializationTests.cs"
    ///         region="ReducingSerializedJsonSizeNullValueHandlingExample" title="NullValueHandling Ignore Example" />
    /// </example>
    public enum NullValueHandling
    {
        /// <summary>
        ///     Include null values when serializing and deserializing objects.
        /// </summary>
        Include = 0,

        /// <summary>
        ///     Ignore null values when serializing and deserializing objects.
        /// </summary>
        Ignore = 1
    }
}