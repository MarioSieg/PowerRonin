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

namespace FluentScheduler
{
    /// <summary>
    ///     Unit of time in days.
    /// </summary>
    public sealed class DayUnit : IDayRestrictableUnit
    {
        private readonly int _duration;

        internal DayUnit(Schedule schedule, int duration)
        {
            _duration = duration < 1 ? 1 : duration;
            Schedule = schedule;
            Schedule.CalculateNextRun = x =>
            {
                var nextRun = x.Date.AddDays(_duration);
                return x > nextRun ? ((IDayRestrictableUnit) this).DayIncrement(nextRun) : nextRun;
            };
        }

        internal Schedule Schedule { get; }

        Schedule IDayRestrictableUnit.Schedule => Schedule;

        DateTime IDayRestrictableUnit.DayIncrement(DateTime increment)
        {
            return increment.AddDays(_duration);
        }

        /// <summary>
        ///     Runs the job at the given time of day.
        /// </summary>
        /// <param name="hours">The hours (0 through 23).</param>
        /// <param name="minutes">The minutes (0 through 59).</param>
        public IDayRestrictableUnit At(int hours, int minutes)
        {
            Schedule.CalculateNextRun = x =>
            {
                var nextRun = x.Date.AddHours(hours).AddMinutes(minutes);
                return x > nextRun ? ((IDayRestrictableUnit) this).DayIncrement(nextRun) : nextRun;
            };
            return this;
        }
    }
}