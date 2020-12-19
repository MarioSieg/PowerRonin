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
using System.Text;

namespace Dreamcast.Lua.Interpreter.Interop.Converters
{
    internal static class StringConversions
    {
        internal static StringSubtype GetStringSubtype(Type desiredType)
        {
            if (desiredType == typeof(string))
                return StringSubtype.String;
            if (desiredType == typeof(StringBuilder))
                return StringSubtype.StringBuilder;
            if (desiredType == typeof(char))
                return StringSubtype.Char;
            return StringSubtype.None;
        }


        internal static object ConvertString(StringSubtype stringSubType, string str, Type desiredType, DataType dataType)
        {
            switch (stringSubType)
            {
                case StringSubtype.String:
                    return str;
                case StringSubtype.StringBuilder:
                    return new StringBuilder(str);
                case StringSubtype.Char:
                    if (!string.IsNullOrEmpty(str))
                        return str[0];
                    break;
                case StringSubtype.None:
                default:
                    break;
            }

            throw ScriptRuntimeException.ConvertObjectFailed(dataType, desiredType);
        }

        internal enum StringSubtype
        {
            None,
            String,
            StringBuilder,
            Char
        }
    }
}