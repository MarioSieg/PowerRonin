using System.Diagnostics;

namespace Dreamcast.Core
{
    public static class Chrono
    {
        private static readonly Stopwatch Clock = new();
        public static uint Cycles { get; private set; }

        public static double DeltaTime { get; private set; }

        public static double Time { get; private set; }

        public static double TimeScale { get; set; } = 1.0;

        internal static void Update()
        {
            ++Cycles;
            DeltaTime = Clock.ElapsedTicks / (double) Stopwatch.Frequency;
            Time += DeltaTime;
            Clock.Restart();
        }
    }
}