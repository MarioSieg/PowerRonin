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

#nullable disable

namespace Dreamcast.Json.Schema
{
    [Obsolete("JSON Schema validation has been moved to its own package. See https://www.newtonsoft.com/jsonschema for more details.")]
    internal static class JsonSchemaConstants
    {
        public const string TypePropertyName = "type";
        public const string PropertiesPropertyName = "properties";
        public const string ItemsPropertyName = "items";
        public const string AdditionalItemsPropertyName = "additionalItems";
        public const string RequiredPropertyName = "required";
        public const string PatternPropertiesPropertyName = "patternProperties";
        public const string AdditionalPropertiesPropertyName = "additionalProperties";
        public const string RequiresPropertyName = "requires";
        public const string MinimumPropertyName = "minimum";
        public const string MaximumPropertyName = "maximum";
        public const string ExclusiveMinimumPropertyName = "exclusiveMinimum";
        public const string ExclusiveMaximumPropertyName = "exclusiveMaximum";
        public const string MinimumItemsPropertyName = "minItems";
        public const string MaximumItemsPropertyName = "maxItems";
        public const string PatternPropertyName = "pattern";
        public const string MaximumLengthPropertyName = "maxLength";
        public const string MinimumLengthPropertyName = "minLength";
        public const string EnumPropertyName = "enum";
        public const string ReadOnlyPropertyName = "readonly";
        public const string TitlePropertyName = "title";
        public const string DescriptionPropertyName = "description";
        public const string FormatPropertyName = "format";
        public const string DefaultPropertyName = "default";
        public const string TransientPropertyName = "transient";
        public const string DivisibleByPropertyName = "divisibleBy";
        public const string HiddenPropertyName = "hidden";
        public const string DisallowPropertyName = "disallow";
        public const string ExtendsPropertyName = "extends";
        public const string IdPropertyName = "id";
        public const string UniqueItemsPropertyName = "uniqueItems";

        public const string OptionValuePropertyName = "value";
        public const string OptionLabelPropertyName = "label";

        public static readonly IDictionary<string, JsonSchemaType> JsonSchemaTypeMapping = new Dictionary<string, JsonSchemaType>
        {
            {"string", JsonSchemaType.String},
            {"object", JsonSchemaType.Object},
            {"integer", JsonSchemaType.Integer},
            {"number", JsonSchemaType.Float},
            {"null", JsonSchemaType.Null},
            {"boolean", JsonSchemaType.Boolean},
            {"array", JsonSchemaType.Array},
            {"any", JsonSchemaType.Any}
        };
    }
}