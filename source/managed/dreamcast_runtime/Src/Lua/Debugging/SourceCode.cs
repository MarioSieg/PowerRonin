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
using System.Collections.Generic;
using System.Text;

namespace Dreamcast.Lua.Interpreter.Debugging
{
    /// <summary>
    ///     Class representing the source code of a given script
    /// </summary>
    public class SourceCode : IScriptPrivateResource
    {
        internal SourceCode(string name, string code, int sourceID, Script ownerScript)
        {
            Refs = new List<SourceRef>();

            List<string> lines = new();

            Name = name;
            Code = code;

            lines.Add(string.Format("-- Begin of chunk : {0} ", name));

            lines.AddRange(Code.Split('\n'));

            Lines = lines.ToArray();

            OwnerScript = ownerScript;
            SourceID = sourceID;
        }

        /// <summary>
        ///     Gets the name of the source code
        /// </summary>
        public string Name { get; }

        /// <summary>
        ///     Gets the source code as a string
        /// </summary>
        public string Code { get; }

        /// <summary>
        ///     Gets the source code lines.
        /// </summary>
        public string[] Lines { get; }

        /// <summary>
        ///     Gets the source identifier inside a script
        /// </summary>
        public int SourceID { get; }

        internal List<SourceRef> Refs { get; }

        /// <summary>
        ///     Gets the script owning this resource.
        /// </summary>
        public Script OwnerScript { get; }

        /// <summary>
        ///     Gets the code snippet represented by a source ref
        /// </summary>
        /// <param name="sourceCodeRef">The source code reference.</param>
        /// <returns></returns>
        public string GetCodeSnippet(SourceRef sourceCodeRef)
        {
            if (sourceCodeRef.FromLine == sourceCodeRef.ToLine)
            {
                var from = AdjustStrIndex(Lines[sourceCodeRef.FromLine], sourceCodeRef.FromChar);
                var to = AdjustStrIndex(Lines[sourceCodeRef.FromLine], sourceCodeRef.ToChar);
                return Lines[sourceCodeRef.FromLine].Substring(from, to - from);
            }

            StringBuilder sb = new();

            for (var i = sourceCodeRef.FromLine; i <= sourceCodeRef.ToLine; i++)
                if (i == sourceCodeRef.FromLine)
                {
                    var from = AdjustStrIndex(Lines[i], sourceCodeRef.FromChar);
                    sb.Append(Lines[i].Substring(@from));
                }
                else if (i == sourceCodeRef.ToLine)
                {
                    var to = AdjustStrIndex(Lines[i], sourceCodeRef.ToChar);
                    sb.Append(Lines[i].Substring(0, to + 1));
                }
                else
                {
                    sb.Append(Lines[i]);
                }

            return sb.ToString();
        }

        private int AdjustStrIndex(string str, int loc)
        {
            return Math.Max(Math.Min(str.Length, loc), 0);
        }
    }
}