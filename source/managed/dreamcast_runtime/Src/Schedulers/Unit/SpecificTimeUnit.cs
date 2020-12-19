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
    ///     Unit of specific time of the day.
    /// </summary>
    public sealed class SpecificTimeUnit
    {
        internal SpecificTimeUnit(Schedule schedule)
        {
            Schedule = schedule;
        }

        internal Schedule Schedule { get; }

        /// <summary>
        ///     Also runs the job according to the given interval.
        /// </summary>
        /// <param name="interval">Interval to wait.</param>
        public TimeUnit AndEvery(int interval)
        {
            var parent = Schedule.Parent ?? Schedule;

            var child =
                new Schedule(Schedule.Jobs) {Parent = parent, Reentrant = parent.Reentrant, Name = parent.Name};

            if (parent.CalculateNextRun != null)
            {
                var now = JobManager.Now;
                var delay = parent.CalculateNextRun(now) - now;

                if (delay > TimeSpan.Zero)
                    child.DelayRunFor = delay;
            }

            child.Parent.AdditionalSchedules.Add(child);
            return child.ToRunEvery(interval);
        }
    }
}