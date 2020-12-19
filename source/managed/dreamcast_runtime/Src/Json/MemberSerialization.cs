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
using Dreamcast.Json.Serialization;

namespace Dreamcast.Json
{
    /// <summary>
    ///     Specifies the member serialization options for the <see cref="JsonSerializer" />.
    /// </summary>
    public enum MemberSerialization
    {
#pragma warning disable 1584,1711,1572,1581,1580,1574
        /// <summary>
        ///     All public members are serialized by default. Members can be excluded using <see cref="JsonIgnoreAttribute" /> or
        ///     <see cref="NonSerializedAttribute" />.
        ///     This is the default member serialization mode.
        /// </summary>
        OptOut = 0,

        /// <summary>
        ///     Only members marked with <see cref="JsonPropertyAttribute" /> or <see cref="DataMemberAttribute" /> are serialized.
        ///     This member serialization mode can also be set by marking the class with <see cref="DataContractAttribute" />.
        /// </summary>
        OptIn = 1,

        /// <summary>
        ///     All public and private fields are serialized. Members can be excluded using <see cref="JsonIgnoreAttribute" /> or
        ///     <see cref="NonSerializedAttribute" />.
        ///     This member serialization mode can also be set by marking the class with <see cref="SerializableAttribute" />
        ///     and setting IgnoreSerializableAttribute on <see cref="DefaultContractResolver" /> to <c>false</c>.
        /// </summary>
        Fields = 2
#pragma warning restore 1584,1711,1572,1581,1580,1574
    }
}