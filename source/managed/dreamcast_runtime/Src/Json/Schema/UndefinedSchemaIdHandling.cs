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
    ///         Specifies undefined schema Id handling options for the <see cref="JsonSchemaGenerator" />.
    ///     </para>
    ///     <note type="caution">
    ///         JSON Schema validation has been moved to its own package. See
    ///         <see href="https://www.newtonsoft.com/jsonschema">https://www.newtonsoft.com/jsonschema</see> for more details.
    ///     </note>
    /// </summary>
    [Obsolete("JSON Schema validation has been moved to its own package. See https://www.newtonsoft.com/jsonschema for more details.")]
    public enum UndefinedSchemaIdHandling
    {
        /// <summary>
        ///     Do not infer a schema Id.
        /// </summary>
        None = 0,

        /// <summary>
        ///     Use the .NET type name as the schema Id.
        /// </summary>
        UseTypeName = 1,

        /// <summary>
        ///     Use the assembly qualified .NET type name as the schema Id.
        /// </summary>
        UseAssemblyQualifiedName = 2
    }
}