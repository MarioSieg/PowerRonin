using System;

namespace PowerRonin.Lua.Interpreter.Diagnostics.PerformanceCounters
{
    internal interface IPerformanceStopwatch
    {
        IDisposable Start();
        PerformanceResult GetResult();
    }
}