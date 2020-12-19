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

namespace Dreamcast.Lua.Interpreter.Loaders
{
    /// <summary>
    ///     A script loader used for platforms we cannot initialize in any better way..
    /// </summary>
    internal class InvalidScriptLoader : IScriptLoader
    {
        private readonly string m_Error;

        internal InvalidScriptLoader(string frameworkname)
        {
            m_Error = string.Format(
                @"Loading scripts from files is not automatically supported on {0}. 
Please implement your own IScriptLoader (possibly, extending ScriptLoaderBase for easier implementation),
use a preexisting loader like EmbeddedResourcesScriptLoader or UnityAssetsScriptLoader or load scripts from strings.", frameworkname);
        }

        public object LoadFile(string file, Table globalContext)
        {
            throw new PlatformNotSupportedException(m_Error);
        }

        public string ResolveFileName(string filename, Table globalContext)
        {
            return filename;
        }

        public string ResolveModuleName(string modname, Table globalContext)
        {
            throw new PlatformNotSupportedException(m_Error);
        }
    }
}