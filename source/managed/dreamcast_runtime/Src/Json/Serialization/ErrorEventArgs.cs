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

namespace Dreamcast.Json.Serialization
{
    /// <summary>
    ///     Provides data for the Error event.
    /// </summary>
    public class ErrorEventArgs : EventArgs
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="ErrorEventArgs" /> class.
        /// </summary>
        /// <param name="currentObject">The current object.</param>
        /// <param name="errorContext">The error context.</param>
        public ErrorEventArgs(object? currentObject, ErrorContext errorContext)
        {
            CurrentObject = currentObject;
            ErrorContext = errorContext;
        }

        /// <summary>
        ///     Gets the current object the error event is being raised against.
        /// </summary>
        /// <value>The current object the error event is being raised against.</value>
        public object? CurrentObject { get; }

        /// <summary>
        ///     Gets the error context.
        /// </summary>
        /// <value>The error context.</value>
        public ErrorContext ErrorContext { get; }
    }
}