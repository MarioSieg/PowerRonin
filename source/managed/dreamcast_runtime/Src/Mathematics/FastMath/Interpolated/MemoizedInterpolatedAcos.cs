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
    public sealed class MemoizedInterpolatedAcos : IMemoizedMethod
    {
        private const int AdditionalValueCount = 3;

        private readonly float _argumentMultiplier;

        private MemoizedInterpolatedAcos(int valuesCount)
        {
            MinArgument = -1;
            MaxArgument = 1;
            Values = new float[valuesCount];
            Step = (MaxArgument - MinArgument) / (valuesCount - AdditionalValueCount);
            this.ProduceValuesArray(AdditionalValueCount);
            _argumentMultiplier = 1 / Step;
        }

        public float MinArgument { get; }

        public float MaxArgument { get; }

        public bool IsLinearInterpolated => true;

        public float Step { get; }

        public float[] Values { get; }

        public Func<float, float> BaseMethod => x => (float) System.Math.Acos(x);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var floatIndex = (argument - MinArgument) * _argumentMultiplier;
            var index = (int) floatIndex;
            var alpha = floatIndex - index;
            return (1 - alpha) * Values[index] + alpha * Values[index + 1];
        }

        public static MemoizedInterpolatedAcos ConstructByValuesCount(int valuesCount)
        {
            return new(valuesCount + AdditionalValueCount);
        }

        public static MemoizedInterpolatedAcos ConstructByMaxError(float maxError)
        {
            return ConstructByStep((float) System.Math.Pow(3 * maxError, 2));
        }

        public static MemoizedInterpolatedAcos ConstructByStep(float step)
        {
            var valuesCount = (int) System.Math.Round(2 / step) + AdditionalValueCount;
            if (valuesCount == AdditionalValueCount) ++valuesCount;
            return new MemoizedInterpolatedAcos(valuesCount);
        }
    }
}