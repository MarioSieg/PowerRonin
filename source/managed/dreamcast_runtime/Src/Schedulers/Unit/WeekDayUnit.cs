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
    ///     Unit of time in weekdays.
    /// </summary>
    public sealed class WeekdayUnit : ITimeRestrictableUnit
    {
        private readonly int _duration;

        internal WeekdayUnit(Schedule schedule, int duration)
        {
            _duration = duration < 1 ? 1 : duration;
            Schedule = schedule;
            Schedule.CalculateNextRun = x =>
            {
                var nextRun = x.Date.NextNWeekday(_duration);
                return x > nextRun || !nextRun.Date.IsWeekday() ? nextRun.NextNWeekday(_duration) : nextRun;
            };
        }

        internal Schedule Schedule { get; }

        Schedule ITimeRestrictableUnit.Schedule => Schedule;

        /// <summary>
        ///     Runs the job at the given time of day.
        /// </summary>
        /// <param name="hours">The hours (0 through 23).</param>
        /// <param name="minutes">The minutes (0 through 59).</param>
        public void At(int hours, int minutes)
        {
            Schedule.CalculateNextRun = x =>
            {
                var nextRun = x.Date.AddHours(hours).AddMinutes(minutes);
                return x > nextRun || !nextRun.Date.IsWeekday() ? nextRun.NextNWeekday(_duration) : nextRun;
            };
        }
    }
}