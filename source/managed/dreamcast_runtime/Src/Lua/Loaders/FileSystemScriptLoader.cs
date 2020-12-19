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

#if DOTNET_CORE || (!(PCL || ENABLE_DOTNET || NETFX_CORE))
using System.IO;

namespace Dreamcast.Lua.Interpreter.Loaders
{
    /// <summary>
    ///     A script loader loading scripts directly from the file system (does not go through platform object)
    /// </summary>
    public class FileSystemScriptLoader : ScriptLoaderBase
    {
        /// <summary>
        ///     Checks if a script file exists.
        /// </summary>
        /// <param name="name">The script filename.</param>
        /// <returns></returns>
        public override bool ScriptFileExists(string name)
        {
            return File.Exists(name);
        }

        /// <summary>
        ///     Opens a file for reading the script code.
        ///     It can return either a string, a byte[] or a Stream.
        ///     If a byte[] is returned, the content is assumed to be a serialized (dumped) bytecode. If it's a string, it's
        ///     assumed to be either a script or the output of a string.dump call. If a Stream, autodetection takes place.
        /// </summary>
        /// <param name="file">The file.</param>
        /// <param name="globalContext">The global context.</param>
        /// <returns>
        ///     A string, a byte[] or a Stream.
        /// </returns>
        public override object LoadFile(string file, Table globalContext)
        {
            return new FileStream(file, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
        }
    }
}
#endif