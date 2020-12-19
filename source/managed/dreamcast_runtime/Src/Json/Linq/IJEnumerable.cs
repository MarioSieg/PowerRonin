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
    ///     Represents a collection of <see cref="JToken" /> objects.
    /// </summary>
    /// <typeparam name="T">The type of token.</typeparam>
    public interface IJEnumerable<
#if HAVE_VARIANT_TYPE_PARAMETERS
        out
#endif
        T> : IEnumerable<T> where T : JToken
    {
        /// <summary>
        ///     Gets the <see cref="IJEnumerable{T}" /> of <see cref="JToken" /> with the specified key.
        /// </summary>
        /// <value></value>
        IJEnumerable<JToken> this[object key] { get; }
    }
}