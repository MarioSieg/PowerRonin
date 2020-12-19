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

namespace MoonSharp.Interpreter.Interop
{
    /// <summary>
    ///     Internal type used by <see cref="AnonWrapper{T}" /> for registration
    /// </summary>
    public class AnonWrapper
    {
    }

    /// <summary>
    ///     Wrapper which allows for easier management of userdata without registering a new userdata type - useful
    ///     if a type which is not exposed to scripts but can be managed as a "black box" by scripts is desired.
    /// </summary>
    /// <typeparam name="T">The type to wrap</typeparam>
    public class AnonWrapper<T> : AnonWrapper
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="AnonWrapper{T}" /> class.
        /// </summary>
        public AnonWrapper()
        {
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="AnonWrapper{T}" /> class.
        /// </summary>
        /// <param name="o">The o.</param>
        public AnonWrapper(T o)
        {
            Value = o;
        }

        /// <summary>
        ///     Gets or sets the value this instance wraps.
        /// </summary>
        public T Value { get; set; }
    }
}