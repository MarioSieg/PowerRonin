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
    ///     Provides an interface to enable a class to return line and position information.
    /// </summary>
    public interface IJsonLineInfo
    {
        /// <summary>
        ///     Gets the current line number.
        /// </summary>
        /// <value>
        ///     The current line number or 0 if no line information is available (for example, when <see cref="HasLineInfo" />
        ///     returns <c>false</c>).
        /// </value>
        int LineNumber { get; }

        /// <summary>
        ///     Gets the current line position.
        /// </summary>
        /// <value>
        ///     The current line position or 0 if no line information is available (for example, when <see cref="HasLineInfo" />
        ///     returns <c>false</c>).
        /// </value>
        int LinePosition { get; }

        /// <summary>
        ///     Gets a value indicating whether the class can return line information.
        /// </summary>
        /// <returns>
        ///     <c>true</c> if <see cref="LineNumber" /> and <see cref="LinePosition" /> can be provided; otherwise, <c>false</c>.
        /// </returns>
        bool HasLineInfo();
    }
}