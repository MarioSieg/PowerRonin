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
    ///     Unit of time that represents day of the week.
    /// </summary>
    public sealed class WeeklyDayOfWeekUnit
    {
        private readonly DayOfWeek _day;
        private readonly int _duration;

        internal WeeklyDayOfWeekUnit(Schedule schedule, int duration, DayOfWeek day)
        {
            _duration = duration;
            _day = day;
            Schedule = schedule;

            if (_duration > 0)
                Schedule.CalculateNextRun = x =>
                {
                    var nextRun = x.Date.AddDays(_duration * 7).ThisOrNext(day);
                    return x > nextRun ? nextRun.AddDays(_duration * 7) : nextRun;
                };
            else
                Schedule.CalculateNextRun = x =>
                {
                    var nextRun = x.Date.Next(day);
                    return x > nextRun ? nextRun.AddDays(7) : nextRun;
                };
        }

        internal Schedule Schedule { get; }

        /// <summary>
        ///     Runs the job at the given time of day.
        /// </summary>
        /// <param name="hours">The hours (0 through 23).</param>
        /// <param name="minutes">The minutes (0 through 59).</param>
        public void At(int hours, int minutes)
        {
            Schedule.CalculateNextRun = x =>
            {
                var nextRun = x.Date.AddDays(_duration * 7).ThisOrNext(_day).AddHours(hours).AddMinutes(minutes);
                return x > nextRun ? nextRun.AddDays(Math.Max(_duration, 1) * 7) : nextRun;
            };
        }
    }
}