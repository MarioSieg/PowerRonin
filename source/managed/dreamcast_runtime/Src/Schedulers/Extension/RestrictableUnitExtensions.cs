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
    ///     Extension class for restrictable units.
    /// </summary>
    public static class RestrictableUnitExtensions
    {
        /// <summary>
        ///     Runs the job between the given start and end hour of day.
        /// </summary>
        /// <param name="unit">The schedule being affected.</param>
        /// <param name="startHour">The start hours (0 through 23).</param>
        /// <param name="startMinute">The start minutes (0 through 59).</param>
        /// <param name="endHour">The end hours (0 through 23).</param>
        /// <param name="endMinute">The end minutes (0 through 59).</param>
        public static ITimeRestrictableUnit Between(this ITimeRestrictableUnit unit,
            int startHour,
            int startMinute,
            int endHour,
            int endMinute)
        {
            if (unit == null)
                throw new ArgumentNullException("unit");

            var timeOfDayRunnableCalculator = new TimeOfDayRunnableCalculator(startHour, startMinute, endHour, endMinute);

            var unboundCalculateNextRun = unit.Schedule.CalculateNextRun;
            unit.Schedule.CalculateNextRun = x =>
            {
                var nextRun = unboundCalculateNextRun(x);

                if (timeOfDayRunnableCalculator.Calculate(nextRun) == TimeOfDayRunnable.TooEarly)
                    nextRun = nextRun.Date.AddHours(startHour).AddMinutes(startMinute);

                while (timeOfDayRunnableCalculator.Calculate(nextRun) != TimeOfDayRunnable.CanRun)
                    nextRun = unboundCalculateNextRun(nextRun);

                return nextRun;
            };

            return unit;
        }

        /// <summary>
        ///     Runs the job only on weekdays.
        ///     <param name="unit">The schedule being affected</param>
        /// </summary>
        public static IDayRestrictableUnit WeekdaysOnly(this IDayRestrictableUnit unit)
        {
            if (unit == null)
                throw new ArgumentNullException("unit");

            var unboundCalculateNextRun = unit.Schedule.CalculateNextRun;
            unit.Schedule.CalculateNextRun = x =>
            {
                var nextRun = unboundCalculateNextRun(x);

                while (!nextRun.IsWeekday())
                    nextRun = unit.DayIncrement(nextRun);

                return nextRun;
            };

            return unit;
        }
    }
}