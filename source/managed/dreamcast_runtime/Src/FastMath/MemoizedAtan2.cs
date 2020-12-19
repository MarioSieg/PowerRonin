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
using System.Runtime.CompilerServices;

namespace FastMath
{
    public class MemoizedAtan2
    {
        private const float Pi = (float) Math.PI;

        private const float MinArgumentValue = 1e-3f;

        private readonly MemoizedAtan _atan;

        private MemoizedAtan2(int valuesCount, float maxArgument)
        {
            _atan = MemoizedAtan.ConstructByValuesCount(valuesCount, maxArgument);
        }

        public MemoizedAtan2(MemoizedAtan atan)
        {
            _atan = atan;
        }

        public static MemoizedAtan2 ConstructByValuesCount(int valuesCount, float maxArgument)
        {
            return new(valuesCount, maxArgument);
        }

        public static MemoizedAtan2 ConstructByMaxError(float maxError)
        {
            return new(MemoizedAtan.ConstructByMaxError(maxError));
        }

        public static MemoizedAtan2 ConstructByStep(float step)
        {
            return new(MemoizedAtan.ConstructByStep(step));
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float y, float x)
        {
            if (Math.Abs(x) < MinArgumentValue) return y < 0 ? -Pi / 2 : Pi / 2;
            if (x > 0)
                return _atan.CalculateUnbound(y / x);
            return y < 0
                ? _atan.CalculateUnbound(y / x) - Pi
                : _atan.CalculateUnbound(y / x) + Pi;
        }
    }
}