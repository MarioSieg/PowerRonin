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
    ///     Specifies type name handling options for the <see cref="JsonSerializer" />.
    /// </summary>
    /// <remarks>
    ///     <see cref="JsonSerializer.TypeNameHandling" /> should be used with caution when your application deserializes JSON
    ///     from an external source.
    ///     Incoming types should be validated with a custom <see cref="JsonSerializer.SerializationBinder" />
    ///     when deserializing with a value other than <see cref="TypeNameHandling.None" />.
    /// </remarks>
    [Flags]
    public enum TypeNameHandling
    {
        /// <summary>
        ///     Do not include the .NET type name when serializing types.
        /// </summary>
        None = 0,

        /// <summary>
        ///     Include the .NET type name when serializing into a JSON object structure.
        /// </summary>
        Objects = 1,

        /// <summary>
        ///     Include the .NET type name when serializing into a JSON array structure.
        /// </summary>
        Arrays = 2,

        /// <summary>
        ///     Always include the .NET type name when serializing.
        /// </summary>
        All = Objects | Arrays,

        /// <summary>
        ///     Include the .NET type name when the type of the object being serialized is not the same as its declared type.
        ///     Note that this doesn't include the root serialized object by default. To include the root object's type name in
        ///     JSON
        ///     you must specify a root type object with
        ///     <see cref="JsonConvert.SerializeObject(object, Type, JsonSerializerSettings)" />
        ///     or <see cref="JsonSerializer.Serialize(JsonWriter, object, Type)" />.
        /// </summary>
        Auto = 4
    }
}