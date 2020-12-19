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
    ///     Specifies how strings are escaped when writing JSON text.
    /// </summary>
    public enum StringEscapeHandling
    {
        /// <summary>
        ///     Only control characters (e.g. newline) are escaped.
        /// </summary>
        Default = 0,

        /// <summary>
        ///     All non-ASCII and control characters (e.g. newline) are escaped.
        /// </summary>
        EscapeNonAscii = 1,

        /// <summary>
        ///     HTML (&lt;, &gt;, &amp;, &apos;, &quot;) and control characters (e.g. newline) are escaped.
        /// </summary>
        EscapeHtml = 2
    }
}