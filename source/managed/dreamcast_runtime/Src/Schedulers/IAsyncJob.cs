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

#if NETSTANDARD2_1
namespace FluentScheduler
{
    using System.Threading.Tasks;

    /// <summary>
    /// Some asynchrounous work to be done.
    /// Make sure there's a parameterless constructor (avoid System.MissingMethodException).
    /// </summary>
    public interface IAsyncJob : IJob
    {
        /// <summary>
        /// Executes the job.
        /// </summary>
        Task ExecuteAsync();

        /// <summary>
        /// Executes the job, synchronously.
        /// </summary>
        void IJob.Execute()
        {
            ExecuteAsync().Wait();
        }
    }
}
#endif