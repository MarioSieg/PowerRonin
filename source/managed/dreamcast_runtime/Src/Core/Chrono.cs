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