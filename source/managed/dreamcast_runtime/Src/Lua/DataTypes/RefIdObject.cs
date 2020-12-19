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

namespace MoonSharp.Interpreter
{
    /// <summary>
    ///     A base class for many MoonSharp objects.
    ///     Helds a ReferenceID property which gets a different value for every object instance, for debugging
    ///     purposes. Note that the ID is not assigned in a thread safe manner for speed reason, so the IDs
    ///     are guaranteed to be unique only if everything is running on one thread at a time.
    /// </summary>
    public class RefIdObject
    {
        private static int s_RefIDCounter;

        /// <summary>
        ///     Gets the reference identifier.
        /// </summary>
        /// <value>
        ///     The reference identifier.
        /// </value>
        public int ReferenceID { get; } = ++s_RefIDCounter;


        /// <summary>
        ///     Formats a string with a type name and a ref-id
        /// </summary>
        /// <param name="typeString">The type name.</param>
        /// <returns></returns>
        public string FormatTypeString(string typeString)
        {
            return string.Format("{0}: {1:X8}", typeString, ReferenceID);
        }
    }
}