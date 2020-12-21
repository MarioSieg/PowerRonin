using System;
using System.Runtime.CompilerServices;
using Dreamcast.Math.Fast.Core;

namespace Dreamcast.Math.Fast.Interpolated
{
    public sealed class MemoizedInterpolatedAsin : IMemoizedMethod
    {
        private const int AdditionalValueCount = 3;

        private readonly float _argumentMultiplier;

        private MemoizedInterpolatedAsin(int valuesCount)
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

        public Func<float, float> BaseMethod => x => (float) System.Math.Asin(x);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var floatIndex = (argument - MinArgument) * _argumentMultiplier;
            var index = (int) floatIndex;
            var alpha = floatIndex - index;
            return (1 - alpha) * Values[index] + alpha * Values[index + 1];
        }

        public static MemoizedInterpolatedAsin ConstructByValuesCount(int valuesCount)
        {
            return new(valuesCount + 2);
        }

        public static MemoizedInterpolatedAsin ConstructByMaxError(float maxError)
        {
            return ConstructByStep((float) System.Math.Pow(3 * maxError, 2));
        }

        public static MemoizedInterpolatedAsin ConstructByStep(float step)
        {
            var valuesCount = (int) System.Math.Round(2 / step) + AdditionalValueCount;
            if (valuesCount == AdditionalValueCount) ++valuesCount;
            return new MemoizedInterpolatedAsin(valuesCount);
        }
    }
}