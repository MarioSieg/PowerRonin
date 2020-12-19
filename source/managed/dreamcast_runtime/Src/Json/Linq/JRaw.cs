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

using System.Globalization;
using System.IO;

namespace Dreamcast.Json.Linq
{
    /// <summary>
    ///     Represents a raw JSON string.
    /// </summary>
    public class JRaw : JValue
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="JRaw" /> class from another <see cref="JRaw" /> object.
        /// </summary>
        /// <param name="other">A <see cref="JRaw" /> object to copy from.</param>
        public JRaw(JRaw other)
            : base(other)
        {
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="JRaw" /> class.
        /// </summary>
        /// <param name="rawJson">The raw json.</param>
        public JRaw(object? rawJson)
            : base(rawJson, JTokenType.Raw)
        {
        }

        /// <summary>
        ///     Creates an instance of <see cref="JRaw" /> with the content of the reader's current token.
        /// </summary>
        /// <param name="reader">The reader.</param>
        /// <returns>An instance of <see cref="JRaw" /> with the content of the reader's current token.</returns>
        public static JRaw Create(JsonReader reader)
        {
            using (var sw = new StringWriter(CultureInfo.InvariantCulture))
            using (var jsonWriter = new JsonTextWriter(sw))
            {
                jsonWriter.WriteToken(reader);

                return new JRaw(sw.ToString());
            }
        }

        internal override JToken CloneToken()
        {
            return new JRaw(this);
        }
    }
}