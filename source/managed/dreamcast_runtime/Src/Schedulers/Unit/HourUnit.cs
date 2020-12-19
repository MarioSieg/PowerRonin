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
    ///     Unit of time in hours.
    /// </summary>
    public sealed class HourUnit : ITimeRestrictableUnit
    {
        private readonly int _duration;

        internal HourUnit(Schedule schedule, int duration)
        {
            _duration = duration < 1 ? 1 : duration;
            Schedule = schedule;
            Schedule.CalculateNextRun = x =>
            {
                var nextRun = x.AddHours(_duration);
                return x > nextRun ? nextRun.AddHours(_duration) : nextRun;
            };
        }

        internal Schedule Schedule { get; }

        Schedule ITimeRestrictableUnit.Schedule => Schedule;

        /// <summary>
        ///     Runs the job at the given minute of the hour.
        /// </summary>
        /// <param name="minutes">The minutes (0 through 59).</param>
        public ITimeRestrictableUnit At(int minutes)
        {
            Schedule.CalculateNextRun = x =>
            {
                var nextRun = x.ClearMinutesAndSeconds().AddMinutes(minutes);
                return _duration == 1 && x < nextRun ? nextRun : nextRun.AddHours(_duration);
            };
            return this;
        }
    }
}