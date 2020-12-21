using System;
using System.Runtime.CompilerServices;
using Dreamcast.Math.Fast.Core;

namespace Dreamcast.Math.Fast
{
    public sealed class MemoizedMethod : IMemoizedMethod
    {
        private readonly float _argumentMultiplier;

        private MemoizedMethod(Func<float, float> baseMethod, float minArgument, float maxArgument, int valuesCount)
        {
            BaseMethod = baseMethod;
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

        public Func<float, float> BaseMethod { get; }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var index = (int) ((argument - MinArgument) * _argumentMultiplier);
            return Values[index];
        }

        public static MemoizedMethod ConstructByValuesCount(Func<float, float> baseMethod, float minArgument,
            float maxArgument, int valuesCount)
        {
            return new(baseMethod, minArgument, maxArgument, valuesCount + 1);
        }

        public static MemoizedMethod ConstructByStep(Func<float, float> baseMethod, float minArgument,
            float maxArgument, float step)
        {
            var valuesCount = (int) System.Math.Round((maxArgument - minArgument) / step) + 1;
            if (valuesCount == 1) valuesCount = 2;
            return new MemoizedMethod(baseMethod, minArgument, maxArgument, valuesCount + 1);
        }
    }
}