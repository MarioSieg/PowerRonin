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
    public sealed class MemoizedTan : IUnboundMethod
    {
        private readonly float _argumentMultiplier;

        private readonly int _valuesCycleLength;

        private MemoizedTan(int valuesCount)
        {
            MinArgument = (float) -Math.PI / 2;
            MaxArgument = (float) Math.PI / 2;
            Values = new float[valuesCount];
            Step = (MaxArgument - MinArgument) / (valuesCount - 1);
            this.ProduceValuesArray();
            Values[0] = (float) Math.Tan(-Math.PI / 2);
            Values[Values.Length - 1] = (float) Math.Tan(Math.PI / 2);
            _argumentMultiplier = 1 / Step;
            _valuesCycleLength = Values.Length - 1;
        }

        public float MinArgument { get; }

        public float MaxArgument { get; }

        public bool IsLinearInterpolated => false;

        public float Step { get; }

        public float[] Values { get; }

        public Func<float, float> BaseMethod => x => (float) Math.Tan(x);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var index = (int) ((argument - MinArgument) * _argumentMultiplier);
            return Values[index];
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float CalculateUnbound(float argument)
        {
            var multiplier = 1;
            if (argument < 0)
            {
                argument = -argument;
                multiplier = -1;
            }

            var index = (int) ((argument - MinArgument) * _argumentMultiplier);
            return multiplier * Values[index % _valuesCycleLength];
        }

        public static MemoizedTan ConstructByValuesCount(int valuesCount)
        {
            return new(valuesCount + 1);
        }

        public static MemoizedTan ConstructByStep(float step)
        {
            var valuesCount = (int) Math.Round(Math.PI / step) + 1;
            return new MemoizedTan(valuesCount);
        }
    }
}