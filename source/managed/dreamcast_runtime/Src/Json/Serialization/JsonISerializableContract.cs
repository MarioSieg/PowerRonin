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

#if HAVE_BINARY_SERIALIZATION
using System;
using System.Runtime.Serialization;

namespace Dreamcast.Json.Serialization
{
    /// <summary>
    /// Contract details for a <see cref="Type"/> used by the <see cref="JsonSerializer"/>.
    /// </summary>
    public class JsonISerializableContract : JsonContainerContract
    {
        /// <summary>
        /// Gets or sets the <see cref="ISerializable"/> object constructor.
        /// </summary>
        /// <value>The <see cref="ISerializable"/> object constructor.</value>
        public ObjectConstructor<object>? ISerializableCreator { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="JsonISerializableContract"/> class.
        /// </summary>
        /// <param name="underlyingType">The underlying type for the contract.</param>
        public JsonISerializableContract(Type underlyingType)
            : base(underlyingType)
        {
            ContractType = JsonContractType.Serializable;
        }
    }
}

#endif