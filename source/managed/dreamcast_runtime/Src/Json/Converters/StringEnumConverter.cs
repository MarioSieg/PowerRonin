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
using System.Globalization;
using Dreamcast.Json.Serialization;
using Dreamcast.Json.Utilities;

#if !HAVE_LINQ

#else
using System.Linq;

#endif

namespace Dreamcast.Json.Converters
{
    /// <summary>
    ///     Converts an <see cref="Enum" /> to and from its name string value.
    /// </summary>
    public class StringEnumConverter : JsonConverter
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="StringEnumConverter" /> class.
        /// </summary>
        public StringEnumConverter()
        {
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="StringEnumConverter" /> class.
        /// </summary>
        /// <param name="camelCaseText"><c>true</c> if the written enum text will be camel case; otherwise, <c>false</c>.</param>
        [Obsolete("StringEnumConverter(bool) is obsolete. Create a converter with StringEnumConverter(NamingStrategy, bool) instead.")]
        public StringEnumConverter(bool camelCaseText)
        {
            if (camelCaseText) NamingStrategy = new CamelCaseNamingStrategy();
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="StringEnumConverter" /> class.
        /// </summary>
        /// <param name="namingStrategy">The naming strategy used to resolve how enum text is written.</param>
        /// <param name="allowIntegerValues">
        ///     <c>true</c> if integers are allowed when serializing and deserializing; otherwise,
        ///     <c>false</c>.
        /// </param>
        public StringEnumConverter(NamingStrategy namingStrategy, bool allowIntegerValues = true)
        {
            NamingStrategy = namingStrategy;
            AllowIntegerValues = allowIntegerValues;
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="StringEnumConverter" /> class.
        /// </summary>
        /// <param name="namingStrategyType">
        ///     The <see cref="System.Type" /> of the
        ///     <see cref="Dreamcast.Json.Serialization.NamingStrategy" /> used to write enum text.
        /// </param>
        public StringEnumConverter(Type namingStrategyType)
        {
            ValidationUtils.ArgumentNotNull(namingStrategyType, nameof(namingStrategyType));

            NamingStrategy = JsonTypeReflector.CreateNamingStrategyInstance(namingStrategyType, null);
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="StringEnumConverter" /> class.
        /// </summary>
        /// <param name="namingStrategyType">
        ///     The <see cref="System.Type" /> of the
        ///     <see cref="Dreamcast.Json.Serialization.NamingStrategy" /> used to write enum text.
        /// </param>
        /// <param name="namingStrategyParameters">
        ///     The parameter list to use when constructing the <see cref="Dreamcast.Json.Serialization.NamingStrategy" />
        ///     described by <paramref name="namingStrategyType" />.
        ///     If <c>null</c>, the default constructor is used.
        ///     When non-<c>null</c>, there must be a constructor defined in the
        ///     <see cref="Dreamcast.Json.Serialization.NamingStrategy" /> that exactly matches the number,
        ///     order, and type of these parameters.
        /// </param>
        public StringEnumConverter(Type namingStrategyType, object[] namingStrategyParameters)
        {
            ValidationUtils.ArgumentNotNull(namingStrategyType, nameof(namingStrategyType));

            NamingStrategy = JsonTypeReflector.CreateNamingStrategyInstance(namingStrategyType, namingStrategyParameters);
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="StringEnumConverter" /> class.
        /// </summary>
        /// <param name="namingStrategyType">
        ///     The <see cref="System.Type" /> of the
        ///     <see cref="Dreamcast.Json.Serialization.NamingStrategy" /> used to write enum text.
        /// </param>
        /// <param name="namingStrategyParameters">
        ///     The parameter list to use when constructing the <see cref="Dreamcast.Json.Serialization.NamingStrategy" />
        ///     described by <paramref name="namingStrategyType" />.
        ///     If <c>null</c>, the default constructor is used.
        ///     When non-<c>null</c>, there must be a constructor defined in the
        ///     <see cref="Dreamcast.Json.Serialization.NamingStrategy" /> that exactly matches the number,
        ///     order, and type of these parameters.
        /// </param>
        /// <param name="allowIntegerValues">
        ///     <c>true</c> if integers are allowed when serializing and deserializing; otherwise,
        ///     <c>false</c>.
        /// </param>
        public StringEnumConverter(Type namingStrategyType, object[] namingStrategyParameters, bool allowIntegerValues)
        {
            ValidationUtils.ArgumentNotNull(namingStrategyType, nameof(namingStrategyType));

            NamingStrategy = JsonTypeReflector.CreateNamingStrategyInstance(namingStrategyType, namingStrategyParameters);
            AllowIntegerValues = allowIntegerValues;
        }

        /// <summary>
        ///     Gets or sets a value indicating whether the written enum text should be camel case.
        ///     The default value is <c>false</c>.
        /// </summary>
        /// <value><c>true</c> if the written enum text will be camel case; otherwise, <c>false</c>.</value>
        [Obsolete("StringEnumConverter.CamelCaseText is obsolete. Set StringEnumConverter.NamingStrategy with CamelCaseNamingStrategy instead.")]
        public bool CamelCaseText
        {
            get => NamingStrategy is CamelCaseNamingStrategy ? true : false;
            set
            {
                if (value)
                {
                    if (NamingStrategy is CamelCaseNamingStrategy) return;

                    NamingStrategy = new CamelCaseNamingStrategy();
                }
                else
                {
                    if (!(NamingStrategy is CamelCaseNamingStrategy)) return;

                    NamingStrategy = null;
                }
            }
        }

        /// <summary>
        ///     Gets or sets the naming strategy used to resolve how enum text is written.
        /// </summary>
        /// <value>The naming strategy used to resolve how enum text is written.</value>
        public NamingStrategy? NamingStrategy { get; set; }

        /// <summary>
        ///     Gets or sets a value indicating whether integer values are allowed when serializing and deserializing.
        ///     The default value is <c>true</c>.
        /// </summary>
        /// <value><c>true</c> if integers are allowed when serializing and deserializing; otherwise, <c>false</c>.</value>
        public bool AllowIntegerValues { get; set; } = true;

        /// <summary>
        ///     Writes the JSON representation of the object.
        /// </summary>
        /// <param name="writer">The <see cref="JsonWriter" /> to write to.</param>
        /// <param name="value">The value.</param>
        /// <param name="serializer">The calling serializer.</param>
        public override void WriteJson(JsonWriter writer, object? value, JsonSerializer serializer)
        {
            if (value == null)
            {
                writer.WriteNull();
                return;
            }

            var e = (Enum) value;

            if (!EnumUtils.TryToString(e.GetType(), value, NamingStrategy, out var enumName))
            {
                if (!AllowIntegerValues) throw JsonSerializationException.Create(null, writer.ContainerPath, "Integer value {0} is not allowed.".FormatWith(CultureInfo.InvariantCulture, e.ToString("D")), null);

                // enum value has no name so write number
                writer.WriteValue(value);
            }
            else
            {
                writer.WriteValue(enumName);
            }
        }

        /// <summary>
        ///     Reads the JSON representation of the object.
        /// </summary>
        /// <param name="reader">The <see cref="JsonReader" /> to read from.</param>
        /// <param name="objectType">Type of the object.</param>
        /// <param name="existingValue">The existing value of object being read.</param>
        /// <param name="serializer">The calling serializer.</param>
        /// <returns>The object value.</returns>
        public override object? ReadJson(JsonReader reader, Type objectType, object? existingValue, JsonSerializer serializer)
        {
            if (reader.TokenType == JsonToken.Null)
            {
                if (!ReflectionUtils.IsNullableType(objectType)) throw JsonSerializationException.Create(reader, "Cannot convert null value to {0}.".FormatWith(CultureInfo.InvariantCulture, objectType));

                return null;
            }

            var isNullable = ReflectionUtils.IsNullableType(objectType);
            var t = isNullable ? Nullable.GetUnderlyingType(objectType) : objectType;

            try
            {
                if (reader.TokenType == JsonToken.String)
                {
                    var enumText = reader.Value?.ToString();

                    if (StringUtils.IsNullOrEmpty(enumText) && isNullable) return null;

                    return EnumUtils.ParseEnum(t, NamingStrategy, enumText!, !AllowIntegerValues);
                }

                if (reader.TokenType == JsonToken.Integer)
                {
                    if (!AllowIntegerValues) throw JsonSerializationException.Create(reader, "Integer value {0} is not allowed.".FormatWith(CultureInfo.InvariantCulture, reader.Value));

                    return ConvertUtils.ConvertOrCast(reader.Value, CultureInfo.InvariantCulture, t);
                }
            }
            catch (Exception ex)
            {
                throw JsonSerializationException.Create(reader, "Error converting value {0} to type '{1}'.".FormatWith(CultureInfo.InvariantCulture, MiscellaneousUtils.ToString(reader.Value), objectType), ex);
            }

            // we don't actually expect to get here.
            throw JsonSerializationException.Create(reader, "Unexpected token {0} when parsing enum.".FormatWith(CultureInfo.InvariantCulture, reader.TokenType));
        }

        /// <summary>
        ///     Determines whether this instance can convert the specified object type.
        /// </summary>
        /// <param name="objectType">Type of the object.</param>
        /// <returns>
        ///     <c>true</c> if this instance can convert the specified object type; otherwise, <c>false</c>.
        /// </returns>
        public override bool CanConvert(Type objectType)
        {
            var t = ReflectionUtils.IsNullableType(objectType)
                ? Nullable.GetUnderlyingType(objectType)
                : objectType;

            return t.IsEnum();
        }
    }
}