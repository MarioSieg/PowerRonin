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

#nullable disable

namespace Dreamcast.Json.Schema
{
    /// <summary>
    ///     <para>
    ///         The value types allowed by the <see cref="JsonSchema" />.
    ///     </para>
    ///     <note type="caution">
    ///         JSON Schema validation has been moved to its own package. See
    ///         <see href="https://www.newtonsoft.com/jsonschema">https://www.newtonsoft.com/jsonschema</see> for more details.
    ///     </note>
    /// </summary>
    [Flags]
    [Obsolete("JSON Schema validation has been moved to its own package. See https://www.newtonsoft.com/jsonschema for more details.")]
    public enum JsonSchemaType
    {
        /// <summary>
        ///     No type specified.
        /// </summary>
        None = 0,

        /// <summary>
        ///     String type.
        /// </summary>
        String = 1,

        /// <summary>
        ///     Float type.
        /// </summary>
        Float = 2,

        /// <summary>
        ///     Integer type.
        /// </summary>
        Integer = 4,

        /// <summary>
        ///     Boolean type.
        /// </summary>
        Boolean = 8,

        /// <summary>
        ///     Object type.
        /// </summary>
        Object = 16,

        /// <summary>
        ///     Array type.
        /// </summary>
        Array = 32,

        /// <summary>
        ///     Null type.
        /// </summary>
        Null = 64,

        /// <summary>
        ///     Any type.
        /// </summary>
        Any = String | Float | Integer | Boolean | Object | Array | Null
    }
}