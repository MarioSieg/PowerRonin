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
using System.Collections.Generic;
using System.Linq;

namespace FluentScheduler
{
    internal class ScheduleCollection
    {
        private readonly object _lock = new();
        private readonly List<Schedule> _schedules = new();

        internal bool Any()
        {
            lock (_lock)
            {
                return _schedules.Any();
            }
        }

        internal void Sort()
        {
            lock (_lock)
            {
                _schedules.Sort((x, y) => DateTime.Compare(x.NextRun, y.NextRun));
            }
        }

        internal IEnumerable<Schedule> All()
        {
            lock (_lock)
            {
                return _schedules;
            }
        }

        internal void Add(Schedule schedule)
        {
            lock (_lock)
            {
                _schedules.Add(schedule);
            }
        }

        internal bool Remove(string name)
        {
            lock (_lock)
            {
                var schedule = Get(name);
                if (schedule == null) return false;

                _schedules.Remove(schedule);
                return true;
            }
        }

        internal bool Remove(Schedule schedule)
        {
            lock (_lock)
            {
                return _schedules.Remove(schedule);
            }
        }

        internal void RemoveAll()
        {
            lock (_lock)
            {
                _schedules.Clear();
            }
        }

        internal Schedule First()
        {
            lock (_lock)
            {
                return _schedules.FirstOrDefault();
            }
        }

        internal Schedule Get(string name)
        {
            lock (_lock)
            {
                return _schedules.FirstOrDefault(x => x.Name == name);
            }
        }
    }
}