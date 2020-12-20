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
using System.Diagnostics;

namespace Dreamcast.Lua.Interpreter.Diagnostics.PerformanceCounters
{
    /// <summary>
    ///     This class is not *really* IDisposable.. it's just use to have a RAII like pattern.
    ///     You are free to reuse this instance after calling Dispose.
    /// </summary>
    internal class GlobalPerformanceStopwatch : IPerformanceStopwatch
    {
        private readonly PerformanceCounter m_Counter;
        private int m_Count;
        private long m_Elapsed;

        public GlobalPerformanceStopwatch(PerformanceCounter perfcounter)
        {
            m_Counter = perfcounter;
        }

        public IDisposable Start()
        {
            return new GlobalPerformanceStopwatch_StopwatchObject(this);
        }

        public PerformanceResult GetResult()
        {
            return new()
            {
                Type = PerformanceCounterType.TimeMilliseconds,
                Global = false,
                Name = m_Counter.ToString(),
                Instances = m_Count,
                Counter = m_Elapsed
            };
        }

        private void SignalStopwatchTerminated(Stopwatch sw)
        {
            m_Elapsed += sw.ElapsedMilliseconds;
            m_Count += 1;
        }

        private class GlobalPerformanceStopwatch_StopwatchObject : IDisposable
        {
            private readonly GlobalPerformanceStopwatch m_Parent;
            private readonly Stopwatch m_Stopwatch;

            public GlobalPerformanceStopwatch_StopwatchObject(GlobalPerformanceStopwatch parent)
            {
                m_Parent = parent;
                m_Stopwatch = Stopwatch.StartNew();
            }

            public void Dispose()
            {
                m_Stopwatch.Stop();
                m_Parent.SignalStopwatchTerminated(m_Stopwatch);
            }
        }
    }
}