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
    ///     Unit of time.
    /// </summary>
    public sealed class TimeUnit
    {
        private readonly int _duration;
        private readonly Schedule _schedule;

        internal TimeUnit(Schedule schedule, int duration)
        {
            _schedule = schedule;
            _duration = duration;
        }

        /// <summary>
        ///     Sets the interval to milliseconds.
        ///     The timing may not be accurated when used with very low intervals.
        /// </summary>
        public MillisecondUnit Milliseconds()
        {
            return new(_schedule, _duration);
        }

        /// <summary>
        ///     Sets the interval to seconds.
        /// </summary>
        public SecondUnit Seconds()
        {
            return new(_schedule, _duration);
        }

        /// <summary>
        ///     Sets the interval to minutes.
        /// </summary>
        public MinuteUnit Minutes()
        {
            return new(_schedule, _duration);
        }

        /// <summary>
        ///     Sets the interval to hours.
        /// </summary>
        public HourUnit Hours()
        {
            return new(_schedule, _duration);
        }

        /// <summary>
        ///     Sets the interval to days.
        /// </summary>
        public DayUnit Days()
        {
            return new(_schedule, _duration);
        }

        /// <summary>
        ///     Sets the interval to weekdays.
        /// </summary>
        public WeekdayUnit Weekdays()
        {
            return new(_schedule, _duration);
        }

        /// <summary>
        ///     Sets the interval to weeks.
        /// </summary>
        public WeekUnit Weeks()
        {
            return new(_schedule, _duration);
        }

        /// <summary>
        ///     Sets the interval to months.
        /// </summary>
        public MonthUnit Months()
        {
            return new(_schedule, _duration);
        }
    }
}