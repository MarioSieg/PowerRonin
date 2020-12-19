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

namespace MoonSharp.Interpreter.IO
{
    /// <summary>
    ///     "Optimized" BinaryWriter which shares strings and use a dumb compression for integers
    /// </summary>
    public class BinDumpBinaryWriter : BinaryWriter
    {
        private readonly Dictionary<string, int> m_StringMap = new();

        public BinDumpBinaryWriter(Stream s) : base(s)
        {
        }

        public BinDumpBinaryWriter(Stream s, Encoding e) : base(s, e)
        {
        }

        public override void Write(uint value)
        {
            var v8 = (byte) value;

            if (v8 == value && v8 != 0x7F && v8 != 0x7E)
            {
                base.Write(v8);
            }
            else
            {
                var v16 = (ushort) value;

                if (v16 == value)
                {
                    base.Write((byte) 0x7F);
                    base.Write(v16);
                }
                else
                {
                    base.Write((byte) 0x7E);
                    base.Write(value);
                }
            }
        }

        public override void Write(int value)
        {
            var vsbyte = (sbyte) value;

            if (vsbyte == value && vsbyte != 0x7F && vsbyte != 0x7E)
            {
                base.Write(vsbyte);
            }
            else
            {
                var vshort = (short) value;

                if (vshort == value)
                {
                    base.Write((sbyte) 0x7F);
                    base.Write(vshort);
                }
                else
                {
                    base.Write((sbyte) 0x7E);
                    base.Write(value);
                }
            }
        }

        public override void Write(string value)
        {
            int pos;

            if (m_StringMap.TryGetValue(value, out pos))
            {
                Write(m_StringMap[value]);
            }
            else
            {
                pos = m_StringMap.Count;
                m_StringMap[value] = pos;

                Write(pos);
                base.Write(value);
            }
        }
    }
}