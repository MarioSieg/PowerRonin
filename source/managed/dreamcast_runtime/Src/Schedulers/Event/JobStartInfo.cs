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
    ///     Information of a job start.
    /// </summary>
    public class JobStartInfo
    {
        /// <summary>
        ///     Name of the job.
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        ///     Date and time of the start.
        /// </summary>
        public DateTime StartTime { get; set; }
    }
}