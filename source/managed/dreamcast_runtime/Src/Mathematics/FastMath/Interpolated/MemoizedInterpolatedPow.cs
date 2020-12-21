using System;
using System.Runtime.CompilerServices;
using Dreamcast.Math.Fast.Core;

namespace Dreamcast.Math.Fast.Interpolated
{
    public sealed class MemoizedInterpolatedPow : IMemoizedMethod
    {
        private const float MinArgumentValue = 1e-3f;

        private const int AdditionalValueCount = 3;

        private readonly float _argumentMultiplier;

        private MemoizedInterpolatedPow(float minArgument, float maxArgument, float power, int valuesCount)
        {
            Power = power;
            MinArgument = minArgument;
            MaxArgument = maxArgument;
            Values = new float[valuesCount];
            Step = (MaxArgument - MinArgument) / (valuesCount - AdditionalValueCount);
            this.ProduceValuesArray(AdditionalValueCount);
            _argumentMultiplier = 1 / Step;
        }

        public float Power { get; }
        public float MinArgument { get; }

        public float MaxArgument { get; }

        public bool IsLinearInterpolated => true;

        public float Step { get; }

        public float[] Values { get; }

        public Func<float, float> BaseMethod => x => (float) System.Math.Pow(x, Power);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var floatIndex = (argument - MinArgument) * _argumentMultiplier;
            var index = (int) floatIndex;
            var alpha = floatIndex - index;
            return (1 - alpha) * Values[index] + alpha * Values[index + 1];
        }

        public static MemoizedInterpolatedPow ConstructByValuesCount(float minArgument, float maxArgument, float power,
            int valuesCount)
        {
            return new(minArgument, maxArgument, power, valuesCount + AdditionalValueCount);
        }

        public static MemoizedInterpolatedPow ConstructByStep(float minArgument, float maxArgument, float power,
            float step)
        {
            var valuesCount = (int) System.Math.Round((maxArgument - minArgument) / step) + AdditionalValueCount;
            return new MemoizedInterpolatedPow(minArgument, maxArgument, power, valuesCount);
        }

        public static MemoizedInterpolatedPow ConstructByMaxError(float minArgument, float maxArgument, float power,
            float maxError)
        {
            var step = GetStepByMaxError(minArgument, maxArgument, power, maxError);
            var valuesCount = (int) ((maxArgument - minArgument) / step) + AdditionalValueCount + 1;
            if (valuesCount == AdditionalValueCount) ++valuesCount;
            return new MemoizedInterpolatedPow(minArgument, maxArgument, power, valuesCount);
        }

        private static float GetStepByMaxError(float minArgument, float maxArgument, float power, float maxError)
        {
            float CalculateStep(float argument)
            {
                var methodDerivative2 = (power - 1) * power * System.Math.Pow(argument, power - 2);
                return (float) System.Math.Pow(System.Math.Abs(8 * maxError / methodDerivative2), 0.5) * 0.8f;
            }

            if (System.Math.Abs(power - 1) < MinArgumentValue) return 1;
            if (power < 0)
                if (minArgument < 0 && 0 < maxArgument
                    || System.Math.Abs(minArgument) < MinArgumentValue
                    || System.Math.Abs(maxArgument) < MinArgumentValue)
                    throw new ArgumentException(
                        "Can't calculate values count: power is less then zero and arguments interval containts zero");

            float step;
            if (power >= 2)
            {
                var arg = System.Math.Max(System.Math.Abs(minArgument), System.Math.Abs(maxArgument));
                step = CalculateStep(arg);
            }
            else
            {
                var arg = System.Math.Min(System.Math.Abs(minArgument), System.Math.Abs(maxArgument));
                step = CalculateStep(arg);
            }

            return step;
        }
    }
}