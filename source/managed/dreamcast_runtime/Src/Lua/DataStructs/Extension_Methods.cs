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
using System.Collections.Generic;

namespace Dreamcast.Lua.Interpreter
{
    /// <summary>
    ///     Extension methods used in the whole project.
    /// </summary>
    internal static class Extension_Methods
    {
        /// <summary>
        ///     Gets a value from the dictionary or returns the default value
        /// </summary>
        /// <typeparam name="TKey">The type of the key.</typeparam>
        /// <typeparam name="TValue">The type of the value.</typeparam>
        /// <param name="dictionary">The dictionary.</param>
        /// <param name="key">The key.</param>
        /// <returns></returns>
        public static TValue GetOrDefault<TKey, TValue>(this Dictionary<TKey, TValue> dictionary, TKey key)
        {
            TValue v;

            if (dictionary.TryGetValue(key, out v))
                return v;

            return default;
        }


        /// <summary>
        ///     Gets a value from the dictionary or creates it
        /// </summary>
        /// <typeparam name="TKey">The type of the key.</typeparam>
        /// <typeparam name="TValue">The type of the value.</typeparam>
        /// <param name="dictionary">The dictionary.</param>
        /// <param name="key">The key.</param>
        /// <param name="creator">A function which will create the value if it doesn't exist.</param>
        /// <returns></returns>
        public static TValue GetOrCreate<TKey, TValue>(this Dictionary<TKey, TValue> dictionary, TKey key, Func<TValue> creator)
        {
            TValue v;

            if (!dictionary.TryGetValue(key, out v))
            {
                v = creator();
                dictionary.Add(key, v);
            }

            return v;
        }
    }
}