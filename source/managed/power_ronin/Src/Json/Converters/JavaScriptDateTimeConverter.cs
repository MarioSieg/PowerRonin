using System;
using System.Globalization;
using PowerRonin.Json.Utilities;

namespace PowerRonin.Json.Converters
{
    /// <summary>
    ///     Converts a <see cref="DateTime" /> to and from a JavaScript <c>Date</c> constructor (e.g. <c>new Date(52231943)</c>
    ///     ).
    /// </summary>
    public class JavaScriptDateTimeConverter : DateTimeConverterBase
    {
        /// <summary>
        ///     Writes the JSON representation of the object.
        /// </summary>
        /// <param name="writer">The <see cref="JsonWriter" /> to write to.</param>
        /// <param name="value">The value.</param>
        /// <param name="serializer">The calling serializer.</param>
        public override void WriteJson(JsonWriter writer, object? value, JsonSerializer serializer)
        {
            long ticks;

            if (value is DateTime dateTime)
            {
                var utcDateTime = dateTime.ToUniversalTime();
                ticks = DateTimeUtils.ConvertDateTimeToJavaScriptTicks(utcDateTime);
            }
#if HAVE_DATE_TIME_OFFSET
            else if (value is DateTimeOffset dateTimeOffset)
            {
                DateTimeOffset utcDateTimeOffset = dateTimeOffset.ToUniversalTime();
                ticks = DateTimeUtils.ConvertDateTimeToJavaScriptTicks(utcDateTimeOffset.UtcDateTime);
            }
#endif
            else
            {
                throw new JsonSerializationException("Expected date object value.");
            }

            writer.WriteStartConstructor("Date");
            writer.WriteValue(ticks);
            writer.WriteEndConstructor();
        }

        /// <summary>
        ///     Reads the JSON representation of the object.
        /// </summary>
        /// <param name="reader">The <see cref="JsonReader" /> to read from.</param>
        /// <param name="objectType">Type of the object.</param>
        /// <param name="existingValue">The existing property value of the JSON that is being converted.</param>
        /// <param name="serializer">The calling serializer.</param>
        /// <returns>The object value.</returns>
        public override object? ReadJson(JsonReader reader, Type objectType, object? existingValue,
            JsonSerializer serializer)
        {
            if (reader.TokenType == JsonToken.Null)
            {
                if (!ReflectionUtils.IsNullable(objectType))
                    throw JsonSerializationException.Create(reader,
                        "Cannot convert null value to {0}.".FormatWith(CultureInfo.InvariantCulture, objectType));

                return null;
            }

            if (reader.TokenType != JsonToken.StartConstructor ||
                !string.Equals(reader.Value?.ToString(), "Date", StringComparison.Ordinal))
                throw JsonSerializationException.Create(reader,
                    "Unexpected token or value when parsing date. Token: {0}, Value: {1}".FormatWith(
                        CultureInfo.InvariantCulture, reader.TokenType, reader.Value));

            if (!JavaScriptUtils.TryGetDateFromConstructorJson(reader, out var d, out var errorMessage))
                throw JsonSerializationException.Create(reader, errorMessage);

#if HAVE_DATE_TIME_OFFSET
            Type t = (ReflectionUtils.IsNullableType(objectType))
                ? Nullable.GetUnderlyingType(objectType)
                : objectType;
            if (t == typeof(DateTimeOffset))
            {
                return new DateTimeOffset(d);
            }
#endif
            return d;
        }
    }
}