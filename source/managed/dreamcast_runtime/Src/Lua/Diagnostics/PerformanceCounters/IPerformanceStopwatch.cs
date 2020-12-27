using System;

namespace Dreamcast.Lua.Interpreter.Diagnostics.PerformanceCounters
{
    internal interface IPerformanceStopwatch
    {
        IDisposable Start();
        PerformanceResult GetResult();
    }
}