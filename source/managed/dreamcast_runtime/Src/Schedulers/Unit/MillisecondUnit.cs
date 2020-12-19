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

namespace FluentScheduler
{
    /// <summary>
    ///     Unit of time in milliseconds.
    /// </summary>
    public sealed class MillisecondUnit : ITimeRestrictableUnit
    {
        private readonly int _duration;

        internal MillisecondUnit(Schedule schedule, int duration)
        {
            _duration = duration;
            Schedule = schedule;
            Schedule.CalculateNextRun = x => x.AddMilliseconds(_duration);
        }

        internal Schedule Schedule { get; }

        Schedule ITimeRestrictableUnit.Schedule => Schedule;
    }
}