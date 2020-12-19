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
using Dreamcast.Json.Utilities;

#nullable disable

namespace Dreamcast.Json.Bson
{
    /// <summary>
    ///     Represents a BSON Oid (object id).
    /// </summary>
    [Obsolete("BSON reading and writing has been moved to its own package. See https://www.nuget.org/packages/Dreamcast.Json.Bson for more details.")]
    public class BsonObjectId
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="BsonObjectId" /> class.
        /// </summary>
        /// <param name="value">The Oid value.</param>
        public BsonObjectId(byte[] value)
        {
            ValidationUtils.ArgumentNotNull(value, nameof(value));
            if (value.Length != 12) throw new ArgumentException("An ObjectId must be 12 bytes", nameof(value));

            Value = value;
        }

        /// <summary>
        ///     Gets or sets the value of the Oid.
        /// </summary>
        /// <value>The value of the Oid.</value>
        public byte[] Value { get; }
    }
}