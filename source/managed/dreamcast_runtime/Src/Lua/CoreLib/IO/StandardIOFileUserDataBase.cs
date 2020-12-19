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

using System.IO;

namespace Dreamcast.Lua.Interpreter.CoreLib.IO
{
    /// <summary>
    ///     Abstract class implementing an unclosable file Lua userdata. Methods are meant to be called by Lua code.
    /// </summary>
    internal class StandardIOFileUserDataBase : StreamFileUserDataBase
    {
        protected override string Close()
        {
            return "cannot close standard file";
        }

        public static StandardIOFileUserDataBase CreateInputStream(Stream stream)
        {
            var f = new StandardIOFileUserDataBase();
            f.Initialize(stream, new StreamReader(stream), null);
            return f;
        }

        public static StandardIOFileUserDataBase CreateOutputStream(Stream stream)
        {
            var f = new StandardIOFileUserDataBase();
            f.Initialize(stream, null, new StreamWriter(stream));
            return f;
        }
    }
}