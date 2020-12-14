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
using System.Diagnostics;

namespace Dreamcast.Core
{
    /// <summary>
    /// Engine core class.
    /// </summary>
    public static class Core
    {
        private static void OnStart()
        {
            var stopwatch = Stopwatch.StartNew();
            PrintInformation();
            Protocol.Info($"Scripting backend online! Boot took: {stopwatch.Elapsed.TotalSeconds}s!");
            Protocol.Separator();
        }

        private static void OnUpdate()
        {
            Input.UpdateMouseCursor();
        }

        private static void OnExit()
        {
            
        }

        /// <summary>
        /// Prints some general system information from System.Environment.
        /// </summary>
        public static void PrintInformation()
        {
            Protocol.Info("C# CLR v." + Environment.Version);
            Protocol.Info("Current directory: " + Environment.CurrentDirectory);
            Protocol.Info("Is 64-bit operating system? " + Environment.Is64BitOperatingSystem);
            Protocol.Info("Is 64-bit process? " + Environment.Is64BitProcess);
            Protocol.Info("Machine: " + Environment.MachineName);
            Protocol.Info("Operating system version: " + Environment.OSVersion);
            Protocol.Info("Processor count: " + Environment.ProcessorCount);
            Protocol.Info("System page size: " + Environment.SystemPageSize);
            Protocol.Info("Tick count: " + Environment.TickCount);
            Protocol.Info("Working set: " + Environment.WorkingSet);
            Protocol.Info("User: " + Environment.UserName);
            Protocol.Info("User domain: " + Environment.UserDomainName);
        }
    }
}