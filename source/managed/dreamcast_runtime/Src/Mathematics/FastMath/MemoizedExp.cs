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
using static System.Math;

namespace Dreamcast.Math.Fast
{
    public class MemoizedExp : IMemoizedMethod
    {
        private const float MinArgumentValue = 1e-5f;

        private readonly float _argumentMultiplier;

        private MemoizedExp(float minArgument, float maxArgument, float @base, int valuesCount)
        {
            Base = @base;
            MinArgument = minArgument;
            MaxArgument = maxArgument;
            Values = new float[valuesCount];
            Step = (MaxArgument - MinArgument) / (valuesCount - 1);
            this.ProduceValuesArray();
            _argumentMultiplier = 1 / Step;
        }

        public float Base { get; }
        public float MinArgument { get; }

        public float MaxArgument { get; }

        public bool IsLinearInterpolated => false;

        public float Step { get; }

        public float[] Values { get; }

        public Func<float, float> BaseMethod => x => (float) Pow(Base, x);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var index = (int) ((argument - MinArgument) * _argumentMultiplier);
            return Values[index];
        }

        public static MemoizedExp ConstructByValuesCount(float minArgument, float maxArgument, float @base, int valuesCount)
        {
            return new(minArgument, maxArgument, @base, valuesCount + 1);
        }

        public static MemoizedExp ConstructByMaxError(float minArgument, float maxArgument, float @base, float maxError)
        {
            var valuesCount = GetValuesCountByMaxError(minArgument, maxArgument, @base, maxError);
            return new MemoizedExp(minArgument, maxArgument, @base, valuesCount);
        }

        public static MemoizedExp ConstructByStep(float minArgument, float maxArgument, float @base, float step)
        {
            var valuesCount = (int) Round((maxArgument - minArgument) / step);
            return new MemoizedExp(minArgument, maxArgument, @base, valuesCount + 1);
        }

        private static int GetValuesCountByMaxError(float minArgument, float maxArgument, float @base, float maxError)
        {
            float CalculateStep(float argument)
            {
                return (float) Abs(Log(maxError + Pow(@base, argument), @base) - argument);
            }

            if (@base < 0) throw new ArgumentException("Can't calculate values count: base is less then zero");

            float step;
            if (@base < MinArgumentValue)
                step = 1;
            else if (@base < 1)
                step = CalculateStep(minArgument);
            else
                step = CalculateStep(maxArgument);
            step *= 0.9f;
            return (int) Round((maxArgument - minArgument) / step);
        }
    }
}