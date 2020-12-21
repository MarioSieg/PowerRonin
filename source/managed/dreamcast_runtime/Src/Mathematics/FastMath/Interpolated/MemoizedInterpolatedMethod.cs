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
using Dreamcast.Math.Fast.Core;

namespace Dreamcast.Math.Fast.Interpolated
{
    public sealed class MemoizedInterpolatedMethod : IMemoizedMethod
    {
        private readonly float _argumentMultiplier;

        private MemoizedInterpolatedMethod(Func<float, float> baseMethod, float minArgument, float maxArgument, int valuesCount)
        {
            BaseMethod = baseMethod;
            MinArgument = minArgument;
            MaxArgument = maxArgument;
            Values = new float[valuesCount];
            Step = (MaxArgument - MinArgument) / (valuesCount - 2);
            this.ProduceValuesArray(2);
            _argumentMultiplier = 1 / Step;
        }

        public float MinArgument { get; }

        public float MaxArgument { get; }

        public bool IsLinearInterpolated => true;

        public float Step { get; }

        public float[] Values { get; }

        public Func<float, float> BaseMethod { get; }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var floatIndex = (argument - MinArgument) * _argumentMultiplier;
            var index = (int) floatIndex;
            var alpha = floatIndex - index;
            return (1 - alpha) * Values[index] + alpha * Values[index + 1];
        }

        public static MemoizedInterpolatedMethod ConstructByValuesCount(Func<float, float> baseMethod, float minArgument, float maxArgument, int valuesCount)
        {
            return new(baseMethod, minArgument, maxArgument, valuesCount + 2);
        }

        public static MemoizedInterpolatedMethod ConstructByStep(Func<float, float> baseMethod, float minArgument, float maxArgument, float step)
        {
            var valuesCount = (int) System.Math.Round((maxArgument - minArgument) / step) + 2;
            if (valuesCount == 2) valuesCount = 3;
            return new MemoizedInterpolatedMethod(baseMethod, minArgument, maxArgument, valuesCount + 2);
        }
    }
}