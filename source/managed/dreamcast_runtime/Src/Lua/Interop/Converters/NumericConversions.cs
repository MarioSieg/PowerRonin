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

namespace Dreamcast.Lua.Interpreter.Interop.Converters
{
    /// <summary>
    ///     Static functions to handle conversions of numeric types
    /// </summary>
    internal static class NumericConversions
    {
        /// <summary>
        ///     HashSet of numeric types
        /// </summary>
        internal static readonly HashSet<Type> NumericTypes;

        /// <summary>
        ///     Array of numeric types in order used for some conversions
        /// </summary>
        internal static readonly Type[] NumericTypesOrdered;

        static NumericConversions()
        {
            NumericTypesOrdered = new[] {typeof(double), typeof(decimal), typeof(float), typeof(long), typeof(int), typeof(short), typeof(sbyte), typeof(ulong), typeof(uint), typeof(ushort), typeof(byte)};
            NumericTypes = new HashSet<Type>(NumericTypesOrdered);
        }

        /// <summary>
        ///     Converts a double to another type
        /// </summary>
        internal static object DoubleToType(Type type, double d)
        {
            type = Nullable.GetUnderlyingType(type) ?? type;

            try
            {
                if (type == typeof(double)) return d;
                if (type == typeof(sbyte)) return Convert.ToSByte(d);
                if (type == typeof(byte)) return Convert.ToByte(d);
                if (type == typeof(short)) return Convert.ToInt16(d);
                if (type == typeof(ushort)) return Convert.ToUInt16(d);
                if (type == typeof(int)) return Convert.ToInt32(d);
                if (type == typeof(uint)) return Convert.ToUInt32(d);
                if (type == typeof(long)) return Convert.ToInt64(d);
                if (type == typeof(ulong)) return Convert.ToUInt64(d);
                if (type == typeof(float)) return Convert.ToSingle(d);
                if (type == typeof(decimal)) return Convert.ToDecimal(d);
            }
            catch (Exception)
            {
            }

            return d;
        }

        /// <summary>
        ///     Converts a type to double
        /// </summary>
        internal static double TypeToDouble(Type type, object d)
        {
            if (type != typeof(double) &&
                type != typeof(sbyte) &&
                type != typeof(byte) &&
                type != typeof(short) &&
                type != typeof(ushort) &&
                type != typeof(int) &&
                type != typeof(uint) &&
                type != typeof(long) &&
                type != typeof(ulong) &&
                type != typeof(float) &&
                type != typeof(decimal))
                return (double) d;

            return Convert.ToDouble(d);
        }
    }
}