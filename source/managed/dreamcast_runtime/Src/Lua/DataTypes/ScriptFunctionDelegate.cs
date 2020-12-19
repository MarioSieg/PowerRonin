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
    ///     A Delegate type which can wrap a script function
    /// </summary>
    /// <param name="args">The arguments.</param>
    /// <returns>The return value of the script function</returns>
    public delegate object ScriptFunctionDelegate(params object[] args);

    /// <summary>
    ///     A Delegate type which can wrap a script function with a generic typed return value
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="args">The arguments.</param>
    /// <returns>The return value of the script function</returns>
    public delegate T ScriptFunctionDelegate<T>(params object[] args);
}