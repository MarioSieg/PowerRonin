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
    ///     Unit of time that represents week and day of week of the month (wow that's confusing).
    /// </summary>
    public sealed class MonthOnDayOfWeekUnit
    {
        private readonly DayOfWeek _dayOfWeek;
        private readonly int _duration;

        private readonly Week _week;

        internal MonthOnDayOfWeekUnit(Schedule schedule, int duration, Week week, DayOfWeek dayOfWeek)
        {
            _duration = duration;
            _week = week;
            _dayOfWeek = dayOfWeek;
            Schedule = schedule;
            At(0, 0);
        }

        internal Schedule Schedule { get; }

        /// <summary>
        ///     Runs the job at the given time of day.
        /// </summary>
        /// <param name="hours">The hours (0 through 23).</param>
        /// <param name="minutes">The minutes (0 through 59).</param>
        public void At(int hours, int minutes)
        {
            if (_week == Week.Last)
                Schedule.CalculateNextRun = x =>
                {
                    var nextRun = x.Date.First().Last(_dayOfWeek).AddHours(hours).AddMinutes(minutes);
                    return x > nextRun ? x.Date.First().AddMonths(_duration).Last(_dayOfWeek).AddHours(hours).AddMinutes(minutes) : nextRun;
                };
            else
                Schedule.CalculateNextRun = x =>
                {
                    var nextRun = x.Date.First().ToWeek(_week).ThisOrNext(_dayOfWeek).AddHours(hours).AddMinutes(minutes);
                    return x > nextRun ? x.Date.First().AddMonths(_duration).ToWeek(_week).ThisOrNext(_dayOfWeek).AddHours(hours).AddMinutes(minutes) : nextRun;
                };
        }
    }
}