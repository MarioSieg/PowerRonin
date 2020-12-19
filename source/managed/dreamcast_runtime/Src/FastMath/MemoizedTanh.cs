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
    public class MemoizedTanh : IMemoizedMethod
    {
        private readonly float _argumentMultiplier;

        private MemoizedTanh(float minArgument, float maxArgument, int valuesCount)
        {
            MinArgument = minArgument;
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

        public Func<float, float> BaseMethod => x => (float) Math.Tanh(x);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var index = (int) ((argument - MinArgument) * _argumentMultiplier);
            return Values[index];
        }

        public static MemoizedTanh ConstructByValuesCount(float minArgument, float maxArgument, int valuesCount)
        {
            return new(minArgument, maxArgument, valuesCount + 1);
        }

        public static MemoizedTanh ConstructByMaxError(float minArgument, float maxArgument, float maxError)
        {
            var valuesCount = GetValuesCountByMaxError(minArgument, maxArgument, maxError);
            return new MemoizedTanh(minArgument, maxArgument, valuesCount);
        }

        public static MemoizedTanh ConstructByStep(float minArgument, float maxArgument, float step)
        {
            var valuesCount = (int) Math.Round((maxArgument - minArgument) / step) + 1;
            return new MemoizedTanh(minArgument, maxArgument, valuesCount);
        }

        private static int GetValuesCountByMaxError(float minArgument, float maxArgument, float maxError)
        {
            var step = maxError * 0.95f;
            return (int) Math.Round((maxArgument - minArgument) / step) + 1;
        }
    }
}