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
using FastMath.Core;

namespace FastMath
{
    public sealed class MemoizedAcos : IMemoizedMethod
    {
        private readonly float _argumentMultiplier;

        private MemoizedAcos(int valuesCount)
        {
            MinArgument = -1;
            MaxArgument = 1;
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

        public Func<float, float> BaseMethod => x => (float) Math.Acos(x);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var index = (int) ((argument - MinArgument) * _argumentMultiplier);
            return Values[index];
        }

        public static MemoizedAcos ConstructByValuesCount(int valuesCount)
        {
            return new(valuesCount + 1);
        }

        public static MemoizedAcos ConstructByMaxError(float maxError)
        {
            var step = 1 - Math.Sin(Math.PI / 2 - maxError);
            step *= 0.95f;
            var valuesCount = (int) (2 / step) + 2;
            return new MemoizedAcos(valuesCount);
        }

        public static MemoizedAcos ConstructByStep(float step)
        {
            var valuesCount = (int) Math.Round(2 / step) + 1;
            return new MemoizedAcos(valuesCount);
        }
    }
}