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

using System.Collections.Generic;

namespace Dreamcast.Json.Linq
{
    /// <summary>
    ///     Compares tokens to determine whether they are equal.
    /// </summary>
    public class JTokenEqualityComparer : IEqualityComparer<JToken>
    {
        /// <summary>
        ///     Determines whether the specified objects are equal.
        /// </summary>
        /// <param name="x">The first object of type <see cref="JToken" /> to compare.</param>
        /// <param name="y">The second object of type <see cref="JToken" /> to compare.</param>
        /// <returns>
        ///     <c>true</c> if the specified objects are equal; otherwise, <c>false</c>.
        /// </returns>
        public bool Equals(JToken x, JToken y)
        {
            return JToken.DeepEquals(x, y);
        }

        /// <summary>
        ///     Returns a hash code for the specified object.
        /// </summary>
        /// <param name="obj">The <see cref="System.Object" /> for which a hash code is to be returned.</param>
        /// <returns>A hash code for the specified object.</returns>
        /// <exception cref="System.ArgumentNullException">
        ///     The type of <paramref name="obj" /> is a reference type and
        ///     <paramref name="obj" /> is <c>null</c>.
        /// </exception>
        public int GetHashCode(JToken obj)
        {
            if (obj == null) return 0;

            return obj.GetDeepHashCode();
        }
    }
}