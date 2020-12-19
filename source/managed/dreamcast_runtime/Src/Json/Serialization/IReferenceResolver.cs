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

namespace Dreamcast.Json.Serialization
{
    /// <summary>
    ///     Used to resolve references when serializing and deserializing JSON by the <see cref="JsonSerializer" />.
    /// </summary>
    public interface IReferenceResolver
    {
        /// <summary>
        ///     Resolves a reference to its object.
        /// </summary>
        /// <param name="context">The serialization context.</param>
        /// <param name="reference">The reference to resolve.</param>
        /// <returns>The object that was resolved from the reference.</returns>
        object ResolveReference(object context, string reference);

        /// <summary>
        ///     Gets the reference for the specified object.
        /// </summary>
        /// <param name="context">The serialization context.</param>
        /// <param name="value">The object to get a reference for.</param>
        /// <returns>The reference to the object.</returns>
        string GetReference(object context, object value);

        /// <summary>
        ///     Determines whether the specified object is referenced.
        /// </summary>
        /// <param name="context">The serialization context.</param>
        /// <param name="value">The object to test for a reference.</param>
        /// <returns>
        ///     <c>true</c> if the specified object is referenced; otherwise, <c>false</c>.
        /// </returns>
        bool IsReferenced(object context, object value);

        /// <summary>
        ///     Adds a reference to the specified object.
        /// </summary>
        /// <param name="context">The serialization context.</param>
        /// <param name="reference">The reference.</param>
        /// <param name="value">The object to reference.</param>
        void AddReference(object context, string reference, object value);
    }
}