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
    ///     The default JSON name table implementation.
    /// </summary>
    public class DefaultJsonNameTable : JsonNameTable
    {
        // used to defeat hashtable DoS attack where someone passes in lots of strings that hash to the same hash code
        private static readonly int HashCodeRandomizer;

        private int _count;
        private Entry[] _entries;
        private int _mask = 31;

        static DefaultJsonNameTable()
        {
            HashCodeRandomizer = Environment.TickCount;
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="DefaultJsonNameTable" /> class.
        /// </summary>
        public DefaultJsonNameTable()
        {
            _entries = new Entry[_mask + 1];
        }

        /// <summary>
        ///     Gets a string containing the same characters as the specified range of characters in the given array.
        /// </summary>
        /// <param name="key">The character array containing the name to find.</param>
        /// <param name="start">The zero-based index into the array specifying the first character of the name.</param>
        /// <param name="length">The number of characters in the name.</param>
        /// <returns>A string containing the same characters as the specified range of characters in the given array.</returns>
        public override string? Get(char[] key, int start, int length)
        {
            if (length == 0) return string.Empty;

            var hashCode = length + HashCodeRandomizer;
            hashCode += (hashCode << 7) ^ key[start];
            var end = start + length;
            for (var i = start + 1; i < end; i++) hashCode += (hashCode << 7) ^ key[i];
            hashCode -= hashCode >> 17;
            hashCode -= hashCode >> 11;
            hashCode -= hashCode >> 5;

            // make sure index is evaluated before accessing _entries, otherwise potential race condition causing IndexOutOfRangeException
            var index = hashCode & _mask;
            var entries = _entries;

            for (var entry = entries[index]; entry != null; entry = entry.Next)
                if (entry.HashCode == hashCode && TextEquals(entry.Value, key, start, length))
                    return entry.Value;

            return null;
        }

        /// <summary>
        ///     Adds the specified string into name table.
        /// </summary>
        /// <param name="key">The string to add.</param>
        /// <remarks>This method is not thread-safe.</remarks>
        /// <returns>The resolved string.</returns>
        public string Add(string key)
        {
            if (key == null) throw new ArgumentNullException(nameof(key));

            var length = key.Length;
            if (length == 0) return string.Empty;

            var hashCode = length + HashCodeRandomizer;
            for (var i = 0; i < key.Length; i++) hashCode += (hashCode << 7) ^ key[i];
            hashCode -= hashCode >> 17;
            hashCode -= hashCode >> 11;
            hashCode -= hashCode >> 5;
            for (var entry = _entries[hashCode & _mask]; entry != null; entry = entry.Next)
                if (entry.HashCode == hashCode && entry.Value.Equals(key, StringComparison.Ordinal))
                    return entry.Value;

            return AddEntry(key, hashCode);
        }

        private string AddEntry(string str, int hashCode)
        {
            var index = hashCode & _mask;
            var entry = new Entry(str, hashCode, _entries[index]);
            _entries[index] = entry;
            if (_count++ == _mask) Grow();
            return entry.Value;
        }

        private void Grow()
        {
            var entries = _entries;
            var newMask = _mask * 2 + 1;
            var newEntries = new Entry[newMask + 1];

            for (var i = 0; i < entries.Length; i++)
            {
                Entry next;
                for (var entry = entries[i]; entry != null; entry = next)
                {
                    var index = entry.HashCode & newMask;
                    next = entry.Next;
                    entry.Next = newEntries[index];
                    newEntries[index] = entry;
                }
            }

            _entries = newEntries;
            _mask = newMask;
        }

        private static bool TextEquals(string str1, char[] str2, int str2Start, int str2Length)
        {
            if (str1.Length != str2Length) return false;

            for (var i = 0; i < str1.Length; i++)
                if (str1[i] != str2[str2Start + i])
                    return false;
            return true;
        }

        private class Entry
        {
            internal readonly int HashCode;
            internal readonly string Value;
            internal Entry Next;

            internal Entry(string value, int hashCode, Entry next)
            {
                Value = value;
                HashCode = hashCode;
                Next = next;
            }
        }
    }
}