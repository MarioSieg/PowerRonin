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
using System.Collections.ObjectModel;
#if !HAVE_LINQ
using Dreamcast.Json.Utilities.LinqBridge;

#else
using System.Linq;

#endif

#nullable disable

namespace Dreamcast.Json.Schema
{
    [Obsolete("JSON Schema validation has been moved to its own package. See https://www.newtonsoft.com/jsonschema for more details.")]
    internal class JsonSchemaNode
    {
        public JsonSchemaNode(JsonSchema schema)
        {
            Schemas = new ReadOnlyCollection<JsonSchema>(new[] {schema});
            Properties = new Dictionary<string, JsonSchemaNode>();
            PatternProperties = new Dictionary<string, JsonSchemaNode>();
            Items = new List<JsonSchemaNode>();

            Id = GetId(Schemas);
        }

        private JsonSchemaNode(JsonSchemaNode source, JsonSchema schema)
        {
            Schemas = new ReadOnlyCollection<JsonSchema>(source.Schemas.Union(new[] {schema}).ToList());
            Properties = new Dictionary<string, JsonSchemaNode>(source.Properties);
            PatternProperties = new Dictionary<string, JsonSchemaNode>(source.PatternProperties);
            Items = new List<JsonSchemaNode>(source.Items);
            AdditionalProperties = source.AdditionalProperties;
            AdditionalItems = source.AdditionalItems;

            Id = GetId(Schemas);
        }

        public string Id { get; }
        public ReadOnlyCollection<JsonSchema> Schemas { get; }
        public Dictionary<string, JsonSchemaNode> Properties { get; }
        public Dictionary<string, JsonSchemaNode> PatternProperties { get; }
        public List<JsonSchemaNode> Items { get; }
        public JsonSchemaNode AdditionalProperties { get; set; }
        public JsonSchemaNode AdditionalItems { get; set; }

        public JsonSchemaNode Combine(JsonSchema schema)
        {
            return new(this, schema);
        }

        public static string GetId(IEnumerable<JsonSchema> schemata)
        {
            return string.Join("-", schemata.Select(s => s.InternalId).OrderBy(id => id, StringComparer.Ordinal)
#if !HAVE_STRING_JOIN_WITH_ENUMERABLE
                    .ToArray()
#endif
            );
        }
    }
}