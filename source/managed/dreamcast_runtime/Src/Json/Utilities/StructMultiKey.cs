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

namespace Dreamcast.Json.Utilities
{
    internal readonly struct StructMultiKey<T1, T2> : IEquatable<StructMultiKey<T1, T2>>
    {
        public readonly T1 Value1;
        public readonly T2 Value2;

        public StructMultiKey(T1 v1, T2 v2)
        {
            Value1 = v1;
            Value2 = v2;
        }

        public override int GetHashCode()
        {
            return (Value1?.GetHashCode() ?? 0) ^ (Value2?.GetHashCode() ?? 0);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is StructMultiKey<T1, T2> key)) return false;

            return Equals(key);
        }

        public bool Equals(StructMultiKey<T1, T2> other)
        {
            return Equals(Value1, other.Value1) && Equals(Value2, other.Value2);
        }
    }
}