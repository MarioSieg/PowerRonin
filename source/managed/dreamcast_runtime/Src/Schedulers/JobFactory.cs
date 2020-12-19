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
    ///     A job factory.
    /// </summary>
    public interface IJobFactory
    {
        /// <summary>
        ///     Instantiate a job of the given type.
        /// </summary>
        /// <typeparam name="T">Type of the job to instantiate</typeparam>
        /// <returns>The instantiated job</returns>
        IJob GetJobInstance<T>() where T : IJob;
    }

    internal class JobFactory : IJobFactory
    {
        IJob IJobFactory.GetJobInstance<T>()
        {
            return Activator.CreateInstance<T>();
        }
    }
}