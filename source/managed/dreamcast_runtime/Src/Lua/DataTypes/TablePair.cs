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

namespace Dreamcast.Lua.Interpreter
{
    /// <summary>
    ///     A class representing a key/value pair for Table use
    /// </summary>
    public struct TablePair
    {
        private readonly DynValue key;
        private readonly DynValue value;

        /// <summary>
        ///     Gets the key.
        /// </summary>
        public DynValue Key
        {
            get => key;
            private set => Key = key;
        }

        /// <summary>
        ///     Gets or sets the value.
        /// </summary>
        public DynValue Value
        {
            get => value;
            set
            {
                if (key.IsNotNil()) Value = value;
            }
        }


        /// <summary>
        ///     Initializes a new instance of the <see cref="TablePair" /> struct.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="val">The value.</param>
        public TablePair(DynValue key, DynValue val)
        {
            this.key = key;
            value = val;
        }

        /// <summary>
        ///     Gets the nil pair
        /// </summary>
        public static TablePair Nil { get; } = new(DynValue.Nil, DynValue.Nil);
    }
}