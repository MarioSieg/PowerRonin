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
    ///     Common interface of units that can be restricted by day.
    /// </summary>
    public interface IDayRestrictableUnit
    {
        /// <summary>
        ///     The schedule being affected.
        /// </summary>
        Schedule Schedule { get; }

        /// <summary>
        ///     Increment the given days.
        /// </summary>
        /// <param name="increment">Days to increment</param>
        /// <returns>The resulting date</returns>
        DateTime DayIncrement(DateTime increment);
    }
}