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
using System.Collections.Generic;
#if !HAVE_LINQ
using Dreamcast.Json.Utilities.LinqBridge;

#else
using System.Linq;

#endif

#nullable disable

namespace Dreamcast.Json.Schema
{
    /// <summary>
    ///     <para>
    ///         Resolves <see cref="JsonSchema" /> from an id.
    ///     </para>
    ///     <note type="caution">
    ///         JSON Schema validation has been moved to its own package. See
    ///         <see href="https://www.newtonsoft.com/jsonschema">https://www.newtonsoft.com/jsonschema</see> for more details.
    ///     </note>
    /// </summary>
    [Obsolete("JSON Schema validation has been moved to its own package. See https://www.newtonsoft.com/jsonschema for more details.")]
    public class JsonSchemaResolver
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonSchemaResolver" /> class.
        /// </summary>
        public JsonSchemaResolver()
        {
            LoadedSchemas = new List<JsonSchema>();
        }

        /// <summary>
        ///     Gets or sets the loaded schemas.
        /// </summary>
        /// <value>The loaded schemas.</value>
        public IList<JsonSchema> LoadedSchemas { get; protected set; }

        /// <summary>
        ///     Gets a <see cref="JsonSchema" /> for the specified reference.
        /// </summary>
        /// <param name="reference">The id.</param>
        /// <returns>A <see cref="JsonSchema" /> for the specified reference.</returns>
        public virtual JsonSchema GetSchema(string reference)
        {
            var schema = LoadedSchemas.SingleOrDefault(s => string.Equals(s.Id, reference, StringComparison.Ordinal));

            if (schema == null) schema = LoadedSchemas.SingleOrDefault(s => string.Equals(s.Location, reference, StringComparison.Ordinal));

            return schema;
        }
    }
}