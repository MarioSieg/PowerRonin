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

namespace Dreamcast.Json
{
    /// <summary>
    ///     Base class for a table of atomized string objects.
    /// </summary>
    public abstract class JsonNameTable
    {
        /// <summary>
        ///     Gets a string containing the same characters as the specified range of characters in the given array.
        /// </summary>
        /// <param name="key">The character array containing the name to find.</param>
        /// <param name="start">The zero-based index into the array specifying the first character of the name.</param>
        /// <param name="length">The number of characters in the name.</param>
        /// <returns>A string containing the same characters as the specified range of characters in the given array.</returns>
        public abstract string? Get(char[] key, int start, int length);
    }
}