using System;
using System.Runtime.CompilerServices;
using Dreamcast.Math.Fast.Core;

namespace Dreamcast.Math.Fast
{
    public sealed class MemoizedSin : IUnboundMethod
    {
        private readonly float _argumentMultiplier;

        private readonly int _valuesCycleLength;

        private MemoizedSin(int valuesCount)
        {
            MinArgument = 0;
            MaxArgument = (float) (System.Math.PI * 2);
            Values = new float[valuesCount];
            Step = MaxArgument / (valuesCount - 1);
            this.ProduceValuesArray();
            _argumentMultiplier = 1 / Step;
            _valuesCycleLength = Values.Length - 1;
        }

        public float MinArgument { get; }

        public float MaxArgument { get; }

        public bool IsLinearInterpolated => false;

        public float Step { get; }

        public float[] Values { get; }

        public Func<float, float> BaseMethod => x => (float) System.Math.Sin(x);

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public float Calculate(float argument)
        {
            var index = (int) (argument * _argumentMultiplier);
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

            var index = (int) (argument * _argumentMultiplier);
            return multiplier * Values[index % _valuesCycleLength];
        }

        public static MemoizedSin ConstructByValuesCount(int valuesCount)
        {
            return new(valuesCount + 1);
        }

        public static MemoizedSin ConstructByMaxError(float maxError)
        {
            return new(GetValuesCountByMaxError(maxError));
        }

        public static MemoizedSin ConstructByStep(float step)
        {
            var valuesCount = (int) System.Math.Round(System.Math.PI * 2 / step) + 1;
            return new MemoizedSin(valuesCount);
        }

        private static int GetValuesCountByMaxError(float maxError)
        {
            return (int) System.Math.Round(3 * System.Math.PI / maxError + 1);
        }
    }
}