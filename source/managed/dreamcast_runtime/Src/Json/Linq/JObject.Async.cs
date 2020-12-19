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

#if HAVE_ASYNC
using System;
using System.Globalization;
using System.Threading;
using System.Threading.Tasks;
using Dreamcast.Json.Utilities;

namespace Dreamcast.Json.Linq
{
    public partial class JObject
    {
        /// <summary>
        /// Writes this token to a <see cref="JsonWriter"/> asynchronously.
        /// </summary>
        /// <param name="writer">A <see cref="JsonWriter"/> into which this method will write.</param>
        /// <param name="cancellationToken">The token to monitor for cancellation requests.</param>
        /// <param name="converters">A collection of <see cref="JsonConverter"/> which will be used when writing the token.</param>
        /// <returns>A <see cref="Task"/> that represents the asynchronous write operation.</returns>
        public override Task WriteToAsync(JsonWriter writer, CancellationToken cancellationToken, params JsonConverter[] converters)
        {
            Task t = writer.WriteStartObjectAsync(cancellationToken);
            if (!t.IsCompletedSucessfully())
            {
                return AwaitProperties(t, 0, writer, cancellationToken, converters);
            }

            for (int i = 0; i < _properties.Count; i++)
            {
                t = _properties[i].WriteToAsync(writer, cancellationToken, converters);
                if (!t.IsCompletedSucessfully())
                {
                    return AwaitProperties(t, i + 1, writer, cancellationToken, converters);
                }
            }

            return writer.WriteEndObjectAsync(cancellationToken);

            // Local functions, params renamed (capitalized) so as not to capture and allocate when calling async
            async Task AwaitProperties(Task task, int i, JsonWriter Writer, CancellationToken CancellationToken, JsonConverter[] Converters)
            {
                await task.ConfigureAwait(false);
                for (; i < _properties.Count; i++)
                {
                    await _properties[i].WriteToAsync(Writer, CancellationToken, Converters).ConfigureAwait(false);
                }

                await Writer.WriteEndObjectAsync(CancellationToken).ConfigureAwait(false);
            }
        }

        /// <summary>
        /// Asynchronously loads a <see cref="JObject"/> from a <see cref="JsonReader"/>.
        /// </summary>
        /// <param name="reader">A <see cref="JsonReader"/> that will be read for the content of the <see cref="JObject"/>.</param>
        /// <param name="cancellationToken">The token to monitor for cancellation requests. The default value is <see cref="CancellationToken.None"/>.</param>
        /// <returns>
        /// A <see cref="Task{TResult}"/> that represents the asynchronous load. The <see cref="Task{TResult}.Result"/>
        /// property returns a <see cref="JObject"/> that contains the JSON that was read from the specified <see cref="JsonReader"/>.</returns>
        public new static Task<JObject> LoadAsync(JsonReader reader, CancellationToken cancellationToken = default)
        {
            return LoadAsync(reader, null, cancellationToken);
        }

        /// <summary>
        /// Asynchronously loads a <see cref="JObject"/> from a <see cref="JsonReader"/>.
        /// </summary>
        /// <param name="reader">A <see cref="JsonReader"/> that will be read for the content of the <see cref="JObject"/>.</param>
        /// <param name="settings">The <see cref="JsonLoadSettings"/> used to load the JSON.
        /// If this is <c>null</c>, default load settings will be used.</param>
        /// <param name="cancellationToken">The token to monitor for cancellation requests. The default value is <see cref="CancellationToken.None"/>.</param>
        /// <returns>
        /// A <see cref="Task{TResult}"/> that represents the asynchronous load. The <see cref="Task{TResult}.Result"/>
        /// property returns a <see cref="JObject"/> that contains the JSON that was read from the specified <see cref="JsonReader"/>.</returns>
        public new static async Task<JObject> LoadAsync(JsonReader reader, JsonLoadSettings? settings, CancellationToken cancellationToken = default)
        {
            ValidationUtils.ArgumentNotNull(reader, nameof(reader));

            if (reader.TokenType == JsonToken.None)
            {
                if (!await reader.ReadAsync(cancellationToken).ConfigureAwait(false))
                {
                    throw JsonReaderException.Create(reader, "Error reading JObject from JsonReader.");
                }
            }

            await reader.MoveToContentAsync(cancellationToken).ConfigureAwait(false);

            if (reader.TokenType != JsonToken.StartObject)
            {
                throw JsonReaderException.Create(reader, "Error reading JObject from JsonReader. Current JsonReader item is not an object: {0}".FormatWith(CultureInfo.InvariantCulture, reader.TokenType));
            }

            JObject o = new JObject();
            o.SetLineInfo(reader as IJsonLineInfo, settings);

            await o.ReadTokenFromAsync(reader, settings, cancellationToken).ConfigureAwait(false);

            return o;
        }
    }
}

#endif