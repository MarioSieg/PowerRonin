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

namespace Dreamcast.Lua.Interpreter.Diagnostics.PerformanceCounters
{
    internal class DummyPerformanceStopwatch : IPerformanceStopwatch, IDisposable
    {
        public static DummyPerformanceStopwatch Instance = new();
        private readonly PerformanceResult m_Result;

        private DummyPerformanceStopwatch()
        {
            m_Result = new PerformanceResult
            {
                Counter = 0,
                Global = true,
                Instances = 0,
                Name = "::dummy::",
                Type = PerformanceCounterType.TimeMilliseconds
            };
        }

        public void Dispose()
        {
        }


        public IDisposable Start()
        {
            return this;
        }

        public PerformanceResult GetResult()
        {
            return m_Result;
        }
    }
}