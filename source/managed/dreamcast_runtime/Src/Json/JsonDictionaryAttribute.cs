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

namespace Dreamcast.Json
{
    /// <summary>
    ///     Instructs the <see cref="JsonSerializer" /> how to serialize the collection.
    /// </summary>
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Interface)]
    public sealed class JsonDictionaryAttribute : JsonContainerAttribute
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonDictionaryAttribute" /> class.
        /// </summary>
        public JsonDictionaryAttribute()
        {
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonDictionaryAttribute" /> class with the specified container Id.
        /// </summary>
        /// <param name="id">The container Id.</param>
        public JsonDictionaryAttribute(string id)
            : base(id)
        {
        }
    }
}