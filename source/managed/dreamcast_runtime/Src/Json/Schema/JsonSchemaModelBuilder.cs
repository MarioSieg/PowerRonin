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
    [Obsolete("JSON Schema validation has been moved to its own package. See https://www.newtonsoft.com/jsonschema for more details.")]
    internal class JsonSchemaModelBuilder
    {
        private JsonSchemaNode _node;
        private Dictionary<JsonSchemaNode, JsonSchemaModel> _nodeModels = new();
        private JsonSchemaNodeCollection _nodes = new();

        public JsonSchemaModel Build(JsonSchema schema)
        {
            _nodes = new JsonSchemaNodeCollection();
            _node = AddSchema(null, schema);

            _nodeModels = new Dictionary<JsonSchemaNode, JsonSchemaModel>();
            var model = BuildNodeModel(_node);

            return model;
        }

        public JsonSchemaNode AddSchema(JsonSchemaNode existingNode, JsonSchema schema)
        {
            string newId;
            if (existingNode != null)
            {
                if (existingNode.Schemas.Contains(schema)) return existingNode;

                newId = JsonSchemaNode.GetId(existingNode.Schemas.Union(new[] {schema}));
            }
            else
            {
                newId = JsonSchemaNode.GetId(new[] {schema});
            }

            if (_nodes.Contains(newId)) return _nodes[newId];

            var currentNode = existingNode != null
                ? existingNode.Combine(schema)
                : new JsonSchemaNode(schema);

            _nodes.Add(currentNode);

            AddProperties(schema.Properties, currentNode.Properties);

            AddProperties(schema.PatternProperties, currentNode.PatternProperties);

            if (schema.Items != null)
                for (var i = 0; i < schema.Items.Count; i++)
                    AddItem(currentNode, i, schema.Items[i]);

            if (schema.AdditionalItems != null) AddAdditionalItems(currentNode, schema.AdditionalItems);

            if (schema.AdditionalProperties != null) AddAdditionalProperties(currentNode, schema.AdditionalProperties);

            if (schema.Extends != null)
                foreach (var jsonSchema in schema.Extends)
                    currentNode = AddSchema(currentNode, jsonSchema);

            return currentNode;
        }

        public void AddProperties(IDictionary<string, JsonSchema> source, IDictionary<string, JsonSchemaNode> target)
        {
            if (source != null)
                foreach (var property in source)
                    AddProperty(target, property.Key, property.Value);
        }

        public void AddProperty(IDictionary<string, JsonSchemaNode> target, string propertyName, JsonSchema schema)
        {
            target.TryGetValue(propertyName, out var propertyNode);

            target[propertyName] = AddSchema(propertyNode, schema);
        }

        public void AddItem(JsonSchemaNode parentNode, int index, JsonSchema schema)
        {
            var existingItemNode = parentNode.Items.Count > index
                ? parentNode.Items[index]
                : null;

            var newItemNode = AddSchema(existingItemNode, schema);

            if (!(parentNode.Items.Count > index))
                parentNode.Items.Add(newItemNode);
            else
                parentNode.Items[index] = newItemNode;
        }

        public void AddAdditionalProperties(JsonSchemaNode parentNode, JsonSchema schema)
        {
            parentNode.AdditionalProperties = AddSchema(parentNode.AdditionalProperties, schema);
        }

        public void AddAdditionalItems(JsonSchemaNode parentNode, JsonSchema schema)
        {
            parentNode.AdditionalItems = AddSchema(parentNode.AdditionalItems, schema);
        }

        private JsonSchemaModel BuildNodeModel(JsonSchemaNode node)
        {
            if (_nodeModels.TryGetValue(node, out var model)) return model;

            model = JsonSchemaModel.Create(node.Schemas);
            _nodeModels[node] = model;

            foreach (var property in node.Properties)
            {
                if (model.Properties == null) model.Properties = new Dictionary<string, JsonSchemaModel>();

                model.Properties[property.Key] = BuildNodeModel(property.Value);
            }

            foreach (var property in node.PatternProperties)
            {
                if (model.PatternProperties == null) model.PatternProperties = new Dictionary<string, JsonSchemaModel>();

                model.PatternProperties[property.Key] = BuildNodeModel(property.Value);
            }

            foreach (var t in node.Items)
            {
                if (model.Items == null) model.Items = new List<JsonSchemaModel>();

                model.Items.Add(BuildNodeModel(t));
            }

            if (node.AdditionalProperties != null) model.AdditionalProperties = BuildNodeModel(node.AdditionalProperties);
            if (node.AdditionalItems != null) model.AdditionalItems = BuildNodeModel(node.AdditionalItems);

            return model;
        }
    }
}