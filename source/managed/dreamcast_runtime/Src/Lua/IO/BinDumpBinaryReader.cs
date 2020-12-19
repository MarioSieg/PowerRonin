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

using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Dreamcast.Lua.Interpreter.IO
{
    /// <summary>
    ///     "Optimized" BinaryReader which shares strings and use a dumb compression for integers
    /// </summary>
    public class BinDumpBinaryReader : BinaryReader
    {
        private readonly List<string> m_Strings = new();

        public BinDumpBinaryReader(Stream s) : base(s)
        {
        }

        public BinDumpBinaryReader(Stream s, Encoding e) : base(s, e)
        {
        }

        public override int ReadInt32()
        {
            var b = base.ReadSByte();

            if (b == 0x7F)
                return base.ReadInt16();
            if (b == 0x7E)
                return base.ReadInt32();
            return b;
        }

        public override uint ReadUInt32()
        {
            var b = base.ReadByte();

            if (b == 0x7F)
                return base.ReadUInt16();
            if (b == 0x7E)
                return base.ReadUInt32();
            return b;
        }

        public override string ReadString()
        {
            var pos = ReadInt32();

            if (pos < m_Strings.Count) return m_Strings[pos];

            if (pos == m_Strings.Count)
            {
                string str = base.ReadString();
                m_Strings.Add(str);
                return str;
            }

            throw new IOException("string map failure");
        }
    }
}