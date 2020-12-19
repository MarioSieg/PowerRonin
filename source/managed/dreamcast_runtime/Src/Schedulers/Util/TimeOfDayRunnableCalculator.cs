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
    internal class TimeOfDayRunnableCalculator
    {
        private readonly int _endHour;

        private readonly int _endMinute;
        private readonly int _startHour;

        private readonly int _startMinute;

        internal TimeOfDayRunnableCalculator(int startHour, int startMinute, int endHour, int endMinute)
        {
            _startHour = startHour;
            _startMinute = startMinute;
            _endHour = endHour;
            _endMinute = endMinute;
        }

        internal TimeOfDayRunnable Calculate(DateTime nextRun)
        {
            if (nextRun.Hour < _startHour || nextRun.Hour == _startHour && nextRun.Minute < _startMinute)
                return TimeOfDayRunnable.TooEarly;

            if (nextRun.Hour < _endHour || nextRun.Hour == _endHour && nextRun.Minute < _endMinute)
                return TimeOfDayRunnable.CanRun;

            return TimeOfDayRunnable.TooLate;
        }
    }
}