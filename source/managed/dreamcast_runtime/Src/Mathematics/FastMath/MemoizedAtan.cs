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

namespace Dreamcast.Math.Fast
{
    public class MemoizedAtan : IUnboundMethod
    {
        private const float MinValue = (float) -System.Math.PI / 2;

        private const float MaxValue = (float) System.Math.PI / 2;

        private readonly float _argumentMultiplier;

        private MemoizedAtan(int valuesCount, float maxArgument)
        {
            MinArgument = -maxArgument;
            MaxArgument = maxArgument;
            Values = new float[valuesCount];
            Step = (MaxArgument - MinArgument) / (valuesCount - 1);
            this.ProduceValuesArray();
            _argumentMultiplier = 1 / Step;
        }

        public float MinArgument { get; }

        public float MaxArgument { get; }

        public bool IsLinearInterpolated => false;

        public float Step { get; }

        public float[] Values { get; }

        public Func<float, float> BaseMethod => x => (float) System.Math.Atan(x);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var index = (int) ((argument - MinArgument) * _argumentMultiplier);
            return Values[index];
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float CalculateUnbound(float argument)
        {
            if (argument < MinArgument)
                return MinValue;
            if (argument > MaxArgument)
                return MaxValue;
            var index = (int) ((argument - MinArgument) * _argumentMultiplier);
            return Values[index];
        }

        public static MemoizedAtan ConstructByValuesCount(int valuesCount, float maxArgument)
        {
            return new(valuesCount + 1, maxArgument);
        }

        public static MemoizedAtan ConstructByMaxError(float maxError)
        {
            maxError *= 0.95f;
            var maxArgument = (float) System.Math.Tan(System.Math.PI / 2 - maxError);
            var valuesCount = (int) (2.5f * maxArgument / maxError + 2);
            return new MemoizedAtan(valuesCount, maxArgument);
        }

        public static MemoizedAtan ConstructByStep(float step)
        {
            var maxError = (float) System.Math.Atan(step);
            var maxArgument = (float) System.Math.Tan(System.Math.PI / 2 - maxError);
            var valuesCount = (int) System.Math.Round(2 * maxArgument / maxError);
            return new MemoizedAtan(valuesCount, maxArgument);
        }
    }
}