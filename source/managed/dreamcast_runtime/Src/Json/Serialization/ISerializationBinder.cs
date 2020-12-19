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
using System.Reflection;

namespace Dreamcast.Json.Serialization
{
    /// <summary>
    ///     Allows users to control class loading and mandate what class to load.
    /// </summary>
    public interface ISerializationBinder
    {
        /// <summary>
        ///     When implemented, controls the binding of a serialized object to a type.
        /// </summary>
        /// <param name="assemblyName">Specifies the <see cref="Assembly" /> name of the serialized object.</param>
        /// <param name="typeName">Specifies the <see cref="System.Type" /> name of the serialized object</param>
        /// <returns>The type of the object the formatter creates a new instance of.</returns>
        Type BindToType(string? assemblyName, string typeName);

        /// <summary>
        ///     When implemented, controls the binding of a serialized object to a type.
        /// </summary>
        /// <param name="serializedType">The type of the object the formatter creates a new instance of.</param>
        /// <param name="assemblyName">Specifies the <see cref="Assembly" /> name of the serialized object.</param>
        /// <param name="typeName">Specifies the <see cref="System.Type" /> name of the serialized object.</param>
        void BindToName(Type serializedType, out string? assemblyName, out string? typeName);
    }
}