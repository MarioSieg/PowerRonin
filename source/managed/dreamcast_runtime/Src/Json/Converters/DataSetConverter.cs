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

#if HAVE_ADO_NET
using System;
using System.Data;
using Dreamcast.Json.Serialization;

namespace Dreamcast.Json.Converters
{
    /// <summary>
    /// Converts a <see cref="DataSet"/> to and from JSON.
    /// </summary>
    public class DataSetConverter : JsonConverter
    {
        /// <summary>
        /// Writes the JSON representation of the object.
        /// </summary>
        /// <param name="writer">The <see cref="JsonWriter"/> to write to.</param>
        /// <param name="value">The value.</param>
        /// <param name="serializer">The calling serializer.</param>
        public override void WriteJson(JsonWriter writer, object? value, JsonSerializer serializer)
        {
            if (value == null)
            {
                writer.WriteNull();
                return;
            }

            DataSet dataSet = (DataSet)value;
            DefaultContractResolver? resolver = serializer.ContractResolver as DefaultContractResolver;

            DataTableConverter converter = new DataTableConverter();

            writer.WriteStartObject();

            foreach (DataTable table in dataSet.Tables)
            {
                writer.WritePropertyName((resolver != null) ? resolver.GetResolvedPropertyName(table.TableName) : table.TableName);

                converter.WriteJson(writer, table, serializer);
            }

            writer.WriteEndObject();
        }

        /// <summary>
        /// Reads the JSON representation of the object.
        /// </summary>
        /// <param name="reader">The <see cref="JsonReader"/> to read from.</param>
        /// <param name="objectType">Type of the object.</param>
        /// <param name="existingValue">The existing value of object being read.</param>
        /// <param name="serializer">The calling serializer.</param>
        /// <returns>The object value.</returns>
        public override object? ReadJson(JsonReader reader, Type objectType, object? existingValue, JsonSerializer serializer)
        {
            if (reader.TokenType == JsonToken.Null)
            {
                return null;
            }

            // handle typed datasets
            DataSet ds = (objectType == typeof(DataSet))
                ? new DataSet()
                : (DataSet)Activator.CreateInstance(objectType);

            DataTableConverter converter = new DataTableConverter();

            reader.ReadAndAssert();

            while (reader.TokenType == JsonToken.PropertyName)
            {
                DataTable dt = ds.Tables[(string)reader.Value!];
                bool exists = (dt != null);

                dt = (DataTable)converter.ReadJson(reader, typeof(DataTable), dt, serializer)!;

                if (!exists)
                {
                    ds.Tables.Add(dt);
                }

                reader.ReadAndAssert();
            }

            return ds;
        }

        /// <summary>
        /// Determines whether this instance can convert the specified value type.
        /// </summary>
        /// <param name="valueType">Type of the value.</param>
        /// <returns>
        /// 	<c>true</c> if this instance can convert the specified value type; otherwise, <c>false</c>.
        /// </returns>
        public override bool CanConvert(Type valueType)
        {
            return typeof(DataSet).IsAssignableFrom(valueType);
        }
    }
}

#endif