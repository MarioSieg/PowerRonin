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
    public sealed class JsonArrayAttribute : JsonContainerAttribute
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonArrayAttribute" /> class.
        /// </summary>
        public JsonArrayAttribute()
        {
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonObjectAttribute" /> class with a flag indicating whether the array
        ///     can contain null items.
        /// </summary>
        /// <param name="allowNullItems">A flag indicating whether the array can contain null items.</param>
        public JsonArrayAttribute(bool allowNullItems)
        {
            AllowNullItems = allowNullItems;
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="JsonArrayAttribute" /> class with the specified container Id.
        /// </summary>
        /// <param name="id">The container Id.</param>
        public JsonArrayAttribute(string id)
            : base(id)
        {
        }

        /// <summary>
        ///     Gets or sets a value indicating whether null items are allowed in the collection.
        /// </summary>
        /// <value><c>true</c> if null items are allowed in the collection; otherwise, <c>false</c>.</value>
        public bool AllowNullItems { get; set; }
    }
}