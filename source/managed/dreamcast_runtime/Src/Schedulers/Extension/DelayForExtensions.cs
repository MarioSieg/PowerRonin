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
    ///     DelayFor extension methods.
    /// </summary>
    public static class DelayForExtensions
    {
        private static DelayTimeUnit DelayFor(Schedule schedule, int interval)
        {
            return new(schedule, interval);
        }

        /// <summary>
        ///     Delays the job for the given interval.
        /// </summary>
        /// <param name="unit">The schedule being affected.</param>
        /// <param name="interval">Interval to wait.</param>
        public static DelayTimeUnit DelayFor(this SpecificTimeUnit unit, int interval)
        {
            if (unit == null)
                throw new ArgumentNullException("unit");

            return DelayFor(unit.Schedule, interval);
        }

        /// <summary>
        ///     Delays the job for the given interval.
        /// </summary>
        /// <param name="unit">The schedule being affected.</param>
        /// <param name="interval">Interval to wait.</param>
        public static DelayTimeUnit DelayFor(this MillisecondUnit unit, int interval)
        {
            if (unit == null)
                throw new ArgumentNullException("unit");

            return DelayFor(unit.Schedule, interval);
        }

        /// <summary>
        ///     Delays the job for the given interval.
        /// </summary>
        /// <param name="unit">The schedule being affected.</param>
        /// <param name="interval">Interval to wait.</param>
        public static DelayTimeUnit DelayFor(this SecondUnit unit, int interval)
        {
            if (unit == null)
                throw new ArgumentNullException("unit");

            return DelayFor(unit.Schedule, interval);
        }

        /// <summary>
        ///     Delays the job for the given interval.
        /// </summary>
        /// <param name="unit">The schedule being affected.</param>
        /// <param name="interval">Interval to wait.</param>
        public static DelayTimeUnit DelayFor(this MinuteUnit unit, int interval)
        {
            if (unit == null)
                throw new ArgumentNullException("unit");

            return DelayFor(unit.Schedule, interval);
        }

        /// <summary>
        ///     Delays the job for the given interval.
        /// </summary>
        /// <param name="unit">The schedule being affected.</param>
        /// <param name="interval">Interval to wait.</param>
        public static DelayTimeUnit DelayFor(this HourUnit unit, int interval)
        {
            if (unit == null)
                throw new ArgumentNullException("unit");

            return DelayFor(unit.Schedule, interval);
        }

        /// <summary>
        ///     Delays the job for the given interval.
        /// </summary>
        /// <param name="unit">The schedule being affected.</param>
        /// <param name="interval">Interval to wait.</param>
        public static DelayTimeUnit DelayFor(this DayUnit unit, int interval)
        {
            if (unit == null)
                throw new ArgumentNullException("unit");

            return DelayFor(unit.Schedule, interval);
        }

        /// <summary>
        ///     Delays the job for the given interval.
        /// </summary>
        /// <param name="unit">The schedule being affected.</param>
        /// <param name="interval">Interval to wait.</param>
        public static DelayTimeUnit DelayFor(this WeekUnit unit, int interval)
        {
            if (unit == null)
                throw new ArgumentNullException("unit");

            return DelayFor(unit.Schedule, interval);
        }

        /// <summary>
        ///     Delays the job for the given interval.
        /// </summary>
        /// <param name="unit">The schedule being affected.</param>
        /// <param name="interval">Interval to wait.</param>
        public static DelayTimeUnit DelayFor(this MonthUnit unit, int interval)
        {
            if (unit == null)
                throw new ArgumentNullException("unit");

            return DelayFor(unit.Schedule, interval);
        }
    }
}