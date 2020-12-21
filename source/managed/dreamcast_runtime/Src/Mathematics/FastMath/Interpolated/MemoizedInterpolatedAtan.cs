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
    public class MemoizedInterpolatedAtan : IUnboundMethod
    {
        private const float MinValue = (float) -System.Math.PI / 2;

        private const float MaxValue = (float) System.Math.PI / 2;

        private const int AdditionalValueCount = 2;

        private static readonly float Max2DerivativeValue = (float) (3 * System.Math.Sqrt(3) / 8);

        private readonly float _argumentMultiplier;

        private MemoizedInterpolatedAtan(int valuesCount, float maxArgument)
        {
            MinArgument = -maxArgument;
            MaxArgument = maxArgument;
            Values = new float[valuesCount];
            Step = 2 * MaxArgument / (valuesCount - AdditionalValueCount);
            this.ProduceValuesArray(AdditionalValueCount);
            _argumentMultiplier = 1 / Step;
        }

        public float MinArgument { get; }

        public float MaxArgument { get; }

        public bool IsLinearInterpolated => true;

        public float Step { get; }

        public float[] Values { get; }

        public Func<float, float> BaseMethod => x => (float) System.Math.Atan(x);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var floatIndex = (argument - MinArgument) * _argumentMultiplier;
            var index = (int) floatIndex;
            var alpha = floatIndex - index;
            return (1 - alpha) * Values[index] + alpha * Values[index + 1];
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float CalculateUnbound(float argument)
        {
            if (argument < MinArgument)
                return MinValue;
            if (argument > MaxArgument)
                return MaxValue;
            var floatIndex = (argument - MinArgument) * _argumentMultiplier;
            var index = (int) floatIndex;
            var alpha = floatIndex - index;
            return (1 - alpha) * Values[index] + alpha * Values[index + 1];
        }

        public static MemoizedInterpolatedAtan ConstructByValuesCount(int valuesCount, float maxArgument)
        {
            return new(valuesCount + AdditionalValueCount, maxArgument);
        }

        public static MemoizedInterpolatedAtan ConstructByMaxError(float maxError)
        {
            maxError *= 0.95f;
            var maxArgument = (float) System.Math.Tan(System.Math.PI / 2 - maxError);
            var step = (float) System.Math.Sqrt(8 * maxError / Max2DerivativeValue);
            var valuesCount = (int) (2 * maxArgument / step + AdditionalValueCount + AdditionalValueCount);
            return new MemoizedInterpolatedAtan(valuesCount, maxArgument);
        }

        public static MemoizedInterpolatedAtan ConstructByStep(float step)
        {
            var maxError = (float) System.Math.Atan(step);
            var maxArgument = (float) System.Math.Tan(System.Math.PI / 2 - maxError);
            var valuesCount = (int) System.Math.Round(2 * maxArgument / maxError + AdditionalValueCount);
            if (valuesCount == AdditionalValueCount) ++valuesCount;
            return new MemoizedInterpolatedAtan(valuesCount, maxArgument);
        }
    }
}