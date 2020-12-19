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
using Dreamcast.Json.Linq;
using Dreamcast.Json.Utilities;

#nullable disable

namespace Dreamcast.Json.Schema
{
    [Obsolete("JSON Schema validation has been moved to its own package. See https://www.newtonsoft.com/jsonschema for more details.")]
    internal class JsonSchemaModel
    {
        public JsonSchemaModel()
        {
            Type = JsonSchemaType.Any;
            AllowAdditionalProperties = true;
            AllowAdditionalItems = true;
            Required = false;
        }

        public bool Required { get; set; }
        public JsonSchemaType Type { get; set; }
        public int? MinimumLength { get; set; }
        public int? MaximumLength { get; set; }
        public double? DivisibleBy { get; set; }
        public double? Minimum { get; set; }
        public double? Maximum { get; set; }
        public bool ExclusiveMinimum { get; set; }
        public bool ExclusiveMaximum { get; set; }
        public int? MinimumItems { get; set; }
        public int? MaximumItems { get; set; }
        public IList<string> Patterns { get; set; }
        public IList<JsonSchemaModel> Items { get; set; }
        public IDictionary<string, JsonSchemaModel> Properties { get; set; }
        public IDictionary<string, JsonSchemaModel> PatternProperties { get; set; }
        public JsonSchemaModel AdditionalProperties { get; set; }
        public JsonSchemaModel AdditionalItems { get; set; }
        public bool PositionalItemsValidation { get; set; }
        public bool AllowAdditionalProperties { get; set; }
        public bool AllowAdditionalItems { get; set; }
        public bool UniqueItems { get; set; }
        public IList<JToken> Enum { get; set; }
        public JsonSchemaType Disallow { get; set; }

        public static JsonSchemaModel Create(IList<JsonSchema> schemata)
        {
            var model = new JsonSchemaModel();

            foreach (var schema in schemata) Combine(model, schema);

            return model;
        }

        private static void Combine(JsonSchemaModel model, JsonSchema schema)
        {
            // Version 3 of the Draft JSON Schema has the default value of Not Required
            model.Required = model.Required || (schema.Required ?? false);
            model.Type = model.Type & (schema.Type ?? JsonSchemaType.Any);

            model.MinimumLength = MathUtils.Max(model.MinimumLength, schema.MinimumLength);
            model.MaximumLength = MathUtils.Min(model.MaximumLength, schema.MaximumLength);

            // not sure what is the best way to combine divisibleBy
            model.DivisibleBy = MathUtils.Max(model.DivisibleBy, schema.DivisibleBy);

            model.Minimum = MathUtils.Max(model.Minimum, schema.Minimum);
            model.Maximum = MathUtils.Max(model.Maximum, schema.Maximum);
            model.ExclusiveMinimum = model.ExclusiveMinimum || (schema.ExclusiveMinimum ?? false);
            model.ExclusiveMaximum = model.ExclusiveMaximum || (schema.ExclusiveMaximum ?? false);

            model.MinimumItems = MathUtils.Max(model.MinimumItems, schema.MinimumItems);
            model.MaximumItems = MathUtils.Min(model.MaximumItems, schema.MaximumItems);
            model.PositionalItemsValidation = model.PositionalItemsValidation || schema.PositionalItemsValidation;
            model.AllowAdditionalProperties = model.AllowAdditionalProperties && schema.AllowAdditionalProperties;
            model.AllowAdditionalItems = model.AllowAdditionalItems && schema.AllowAdditionalItems;
            model.UniqueItems = model.UniqueItems || schema.UniqueItems;
            if (schema.Enum != null)
            {
                if (model.Enum == null) model.Enum = new List<JToken>();

                model.Enum.AddRangeDistinct(schema.Enum, JToken.EqualityComparer);
            }

            model.Disallow = model.Disallow | (schema.Disallow ?? JsonSchemaType.None);

            if (schema.Pattern != null)
            {
                if (model.Patterns == null) model.Patterns = new List<string>();

                model.Patterns.AddDistinct(schema.Pattern);
            }
        }
    }
}