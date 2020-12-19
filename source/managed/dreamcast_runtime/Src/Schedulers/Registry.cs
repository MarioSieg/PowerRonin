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
using System.Collections;
using System.Collections.Generic;

namespace FluentScheduler
{
    /// <summary>
    ///     A registry of job schedules.
    /// </summary>
    public class Registry
    {
        private bool _allJobsConfiguredAsNonReentrant;

        /// <summary>
        ///     Default ctor.
        /// </summary>
        public Registry()
        {
            _allJobsConfiguredAsNonReentrant = false;
            Schedules = new List<Schedule>();
        }

        internal List<Schedule> Schedules { get; }

        /// <summary>
        ///     Sets all jobs in this schedule as non reentrant.
        /// </summary>
        public void NonReentrantAsDefault()
        {
            _allJobsConfiguredAsNonReentrant = true;
            lock (((ICollection) Schedules).SyncRoot)
            {
                foreach (var schedule in Schedules)
                    schedule.NonReentrant();
            }
        }

        /// <summary>
        ///     Schedules a new job in the registry.
        /// </summary>
        /// <param name="job">Job to run.</param>
        public Schedule Schedule(Action job)
        {
            if (job == null)
                throw new ArgumentNullException("job");

            return Schedule(job, null);
        }

        /// <summary>
        ///     Schedules a new job in the registry.
        /// </summary>
        /// <param name="job">Job to run.</param>
        public Schedule Schedule(IJob job)
        {
            if (job == null)
                throw new ArgumentNullException("job");

            return Schedule(JobManager.GetJobAction(job), null);
        }

        /// <summary>
        ///     Schedules a new job in the registry.
        /// </summary>
        /// <typeparam name="T">Job to schedule.</typeparam>
        public Schedule Schedule<T>() where T : IJob
        {
            return Schedule(JobManager.GetJobAction<T>(), typeof(T).Name);
        }

        /// <summary>
        ///     Schedules a new job in the registry.
        /// </summary>
        /// <param name="job">Factory method creating a IJob instance to run.</param>
        public Schedule Schedule(Func<IJob> job)
        {
            if (job == null)
                throw new ArgumentNullException("job");

            return Schedule(JobManager.GetJobAction(job), null);
        }

        private Schedule Schedule(Action action, string name)
        {
            var schedule = new Schedule(action);

            if (_allJobsConfiguredAsNonReentrant)
                schedule.NonReentrant();

            lock (((ICollection) Schedules).SyncRoot)
            {
                Schedules.Add(schedule);
            }

            schedule.Name = name;

            return schedule;
        }
    }
}