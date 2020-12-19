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

namespace MoonSharp.Interpreter.Diagnostics.PerformanceCounters
{
    /// <summary>
    ///     This class is not *really* IDisposable.. it's just use to have a RAII like pattern.
    ///     You are free to reuse this instance after calling Dispose.
    /// </summary>
    internal class PerformanceStopwatch : IDisposable, IPerformanceStopwatch
    {
        private int m_Count;
        private readonly PerformanceCounter m_Counter;
        private int m_Reentrant;
        private readonly Stopwatch m_Stopwatch = new();

        public PerformanceStopwatch(PerformanceCounter perfcounter)
        {
            m_Counter = perfcounter;
        }

        public void Dispose()
        {
            m_Reentrant -= 1;

            if (m_Reentrant == 0) m_Stopwatch.Stop();
        }


        public IDisposable Start()
        {
            if (m_Reentrant == 0)
            {
                m_Count += 1;
                m_Stopwatch.Start();
            }

            m_Reentrant += 1;

            return this;
        }

        public PerformanceResult GetResult()
        {
            return new()
            {
                Type = PerformanceCounterType.TimeMilliseconds,
                Global = false,
                Name = m_Counter.ToString(),
                Instances = m_Count,
                Counter = m_Stopwatch.ElapsedMilliseconds
            };
        }
    }
}