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
    ///     Unit used to represent delay.
    /// </summary>
    public sealed class DelayTimeUnit
    {
        private readonly int _interval;

        internal DelayTimeUnit(Schedule schedule, int interval)
        {
            _interval = interval;
            Schedule = schedule;
        }

        internal Schedule Schedule { get; }

        /// <summary>
        ///     Sets the interval to milliseconds.
        ///     The timing may not be accurated when used with very low intervals.
        /// </summary>
        public void Milliseconds()
        {
            Schedule.DelayRunFor = TimeSpan.FromMilliseconds(_interval);
        }

        /// <summary>
        ///     Sets the interval to seconds.
        /// </summary>
        public void Seconds()
        {
            Schedule.DelayRunFor = TimeSpan.FromSeconds(_interval);
        }

        /// <summary>
        ///     Sets the interval to minutes.
        /// </summary>
        public void Minutes()
        {
            Schedule.DelayRunFor = TimeSpan.FromMinutes(_interval);
        }

        /// <summary>
        ///     Sets the interval to hours.
        /// </summary>
        public void Hours()
        {
            Schedule.DelayRunFor = TimeSpan.FromHours(_interval);
        }

        /// <summary>
        ///     Sets the interval to days.
        /// </summary>
        public void Days()
        {
            Schedule.DelayRunFor = TimeSpan.FromDays(_interval);
        }

        /// <summary>
        ///     Sets the interval to weeks.
        /// </summary>
        public void Weeks()
        {
            Schedule.DelayRunFor = TimeSpan.FromDays(_interval * 7);
        }

        /// <summary>
        ///     Sets the interval to months.
        /// </summary>
        public void Months()
        {
            var today = DateTime.Today;
            Schedule.DelayRunFor = today.AddMonths(_interval).Subtract(today);
        }

        /// <summary>
        ///     Sets the interval to years.
        /// </summary>
        public void Years()
        {
            var today = DateTime.Today;
            Schedule.DelayRunFor = today.AddYears(_interval).Subtract(today);
        }
    }
}