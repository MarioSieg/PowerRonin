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
using System.Text;

namespace MoonSharp.Interpreter.CoreLib.IO
{
    /// <summary>
    ///     Abstract class implementing a file Lua userdata. Methods are meant to be called by Lua code.
    /// </summary>
    internal class FileUserData : StreamFileUserDataBase
    {
        public FileUserData(Script script, string filename, Encoding encoding, string mode)
        {
            Stream stream = Script.GlobalOptions.Platform.IO_OpenFile(script, filename, encoding, mode);

            StreamReader reader = stream.CanRead ? new StreamReader(stream, encoding) : null;
            StreamWriter writer = stream.CanWrite ? new StreamWriter(stream, encoding) : null;

            Initialize(stream, reader, writer);
        }
    }
}