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
using System.ComponentModel;

namespace Dreamcast.Json
{
    /// <summary>
    ///     Specifies default value handling options for the <see cref="JsonSerializer" />.
    /// </summary>
    /// <example>
    ///     <code lang="cs" source="..\Src\Dreamcast.Json.Tests\Documentation\SerializationTests.cs"
    ///         region="ReducingSerializedJsonSizeDefaultValueHandlingObject" title="DefaultValueHandling Class" />
    ///     <code lang="cs" source="..\Src\Dreamcast.Json.Tests\Documentation\SerializationTests.cs"
    ///         region="ReducingSerializedJsonSizeDefaultValueHandlingExample" title="DefaultValueHandling Ignore Example" />
    /// </example>
    [Flags]
    public enum DefaultValueHandling
    {
        /// <summary>
        ///     Include members where the member value is the same as the member's default value when serializing objects.
        ///     Included members are written to JSON. Has no effect when deserializing.
        /// </summary>
        Include = 0,

        /// <summary>
        ///     Ignore members where the member value is the same as the member's default value when serializing objects
        ///     so that it is not written to JSON.
        ///     This option will ignore all default values (e.g. <c>null</c> for objects and nullable types; <c>0</c> for integers,
        ///     decimals and floating point numbers; and <c>false</c> for booleans). The default value ignored can be changed by
        ///     placing the <see cref="DefaultValueAttribute" /> on the property.
        /// </summary>
        Ignore = 1,

        /// <summary>
        ///     Members with a default value but no JSON will be set to their default value when deserializing.
        /// </summary>
        Populate = 2,

        /// <summary>
        ///     Ignore members where the member value is the same as the member's default value when serializing objects
        ///     and set members to their default value when deserializing.
        /// </summary>
        IgnoreAndPopulate = Ignore | Populate
    }
}