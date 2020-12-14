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
    ///     Engine core class.
    /// </summary>
    public static class Core
    {
        private static void OnSystemStart()
        {
            PrintInformation();
            Protocol.Info($"Scripting backend online!");
            Protocol.Separator();
        }

        private static void OnSystemUpdate()
        {
            Input.UpdateMouseCursor();
        }

        private static void OnSystemExit()
        {
        }

        /// <summary>
        ///     Prints some general system information from System.Environment.
        /// </summary>
        public static void PrintInformation()
        {
            Protocol.Info("C# CLR v." + Environment.Version);
            Protocol.Info("Current directory: " + Environment.CurrentDirectory);
            Protocol.Info("Machine: " + Environment.MachineName);
            Protocol.Info("Operating system version: " + Environment.OSVersion);
            Protocol.Info("Logical cores: " + Environment.ProcessorCount);
            Protocol.Info("User: " + Environment.UserName);
        }
    }
}