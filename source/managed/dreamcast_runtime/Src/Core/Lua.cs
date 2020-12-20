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

using Dreamcast.Lua.Interpreter;

namespace Dreamcast.Core
{
    /// <summary>
    ///     Contains helpers and methods to execute Lua scripts.
    /// </summary>
    public static class Lua
    {
        /// <summary>
        /// Runs a lua script file.
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public static DynValue RunScript(string filePath)
        {
            return Script.RunFile(filePath);
        }

        /// <summary>
        /// Runs a script as string.
        /// </summary>
        /// <param name="scriptText"></param>
        /// <returns></returns>
        public static DynValue RunString(string scriptText)
        {
            return Script.RunString(scriptText);
        }
    }
}