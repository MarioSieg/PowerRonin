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

#pragma warning disable 1591


namespace Dreamcast.Lua.Interpreter.CoreLib.StringLib
{
    internal class StringRange
    {
        public StringRange()
        {
            Start = 0;
            End = 0;
        }

        public StringRange(int start, int end)
        {
            Start = start;
            End = end;
        }

        public int Start { get; set; }
        public int End { get; set; }

        public static StringRange FromLuaRange(DynValue start, DynValue end, int? defaultEnd = null)
        {
            var i = start.IsNil() ? 1 : (int) start.Number;
            var j = end.IsNil() ? defaultEnd ?? i : (int) end.Number;

            return new StringRange(i, j);
        }


        // Returns the substring of s that starts at i and continues until j; i and j can be negative. 
        // If, after the translation of negative indices, i is less than 1, it is corrected to 1. 
        // If j is greater than the string length, it is corrected to that length. 
        // If, after these corrections, i is greater than j, the function returns the empty string. 		
        public string ApplyToString(string value)
        {
            var i = Start < 0 ? Start + value.Length + 1 : Start;
            var j = End < 0 ? End + value.Length + 1 : End;

            if (i < 1) i = 1;
            if (j > value.Length) j = value.Length;

            if (i > j)
                return string.Empty;

            return value.Substring(i - 1, j - i + 1);
        }

        public int Length()
        {
            return End - Start + 1;
        }
    }
}