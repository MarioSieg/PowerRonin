using System;
using System.Runtime.CompilerServices;
using Dreamcast.Math.Fast.Core;

namespace Dreamcast.Math.Fast
{
    public sealed class MemoizedTan : IUnboundMethod
    {
        private readonly float _argumentMultiplier;

        private readonly int _valuesCycleLength;

        private MemoizedTan(int valuesCount)
        {
            MinArgument = (float) -System.Math.PI / 2;
            MaxArgument = (float) System.Math.PI / 2;
            Values = new float[valuesCount];
            Step = (MaxArgument - MinArgument) / (valuesCount - 1);
            this.ProduceValuesArray();
            Values[0] = (float) System.Math.Tan(-System.Math.PI / 2);
            Values[Values.Length - 1] = (float) System.Math.Tan(System.Math.PI / 2);
            _argumentMultiplier = 1 / Step;
            _valuesCycleLength = Values.Length - 1;
        }

        public float MinArgument { get; }

        public float MaxArgument { get; }

        public bool IsLinearInterpolated => false;

        public float Step { get; }

        public float[] Values { get; }

        public Func<float, float> BaseMethod => x => (float) System.Math.Tan(x);

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
            var valuesCount = (int) System.Math.Round(System.Math.PI / step) + 1;
            return new MemoizedTan(valuesCount);
        }
    }
}