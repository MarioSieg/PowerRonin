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
    public sealed class MemoizedCos : IUnboundMethod
    {
        private readonly float _argumentMultiplier;

        private readonly int _valuesCycleLength;

        private MemoizedCos(int valuesCount)
        {
            MinArgument = 0;
            MaxArgument = (float) (System.Math.PI * 2);
            Values = new float[valuesCount];
            Step = (MaxArgument - MinArgument) / (valuesCount - 1);
            this.ProduceValuesArray();
            _argumentMultiplier = 1 / Step;
            _valuesCycleLength = Values.Length - 1;
        }

        public float MinArgument { get; }

        public float MaxArgument { get; }

        public bool IsLinearInterpolated => false;

        public float Step { get; }

        public float[] Values { get; }

        public Func<float, float> BaseMethod => x => (float) System.Math.Cos(x);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var index = (int) (argument * _argumentMultiplier);
            return Values[index];
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float CalculateUnbound(float argument)
        {
            if (argument < 0) argument = -argument;
            var index = (int) (argument * _argumentMultiplier);
            return Values[index % _valuesCycleLength];
        }

        public static MemoizedCos ConstructByValuesCount(int valuesCount)
        {
            return new(valuesCount + 1);
        }

        public static MemoizedCos ConstructByMaxError(float maxError)
        {
            return new(GetValuesCountByMaxError(maxError));
        }

        public static MemoizedCos ConstructByStep(float step)
        {
            var valuesCount = (int) System.Math.Round(System.Math.PI * 2 / step) + 1;
            return new MemoizedCos(valuesCount);
        }

        private static int GetValuesCountByMaxError(float maxError)
        {
            return (int) System.Math.Round(3 * System.Math.PI / maxError + 1);
        }
    }
}