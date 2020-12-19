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

namespace Dreamcast.Lua.Interpreter
{
    /// <summary>
    ///     Exception thrown when a dynamic expression is invalid
    /// </summary>
#if !(PCL || ((!UNITY_EDITOR) && (ENABLE_DOTNET)) || NETFX_CORE)
    [Serializable]
#endif
    public class DynamicExpressionException : ScriptRuntimeException
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="DynamicExpressionException" /> class.
        /// </summary>
        /// <param name="format">The format.</param>
        /// <param name="args">The arguments.</param>
        public DynamicExpressionException(string format, params object[] args)
            : base("<dynamic>: " + format, args)
        {
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="DynamicExpressionException" /> class.
        /// </summary>
        /// <param name="message">The message.</param>
        public DynamicExpressionException(string message)
            : base("<dynamic>: " + message)
        {
        }
    }
}