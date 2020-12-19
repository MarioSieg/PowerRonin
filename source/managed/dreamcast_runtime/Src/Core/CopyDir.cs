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

using System.IO;

namespace Dreamcast.Core
{
    /// <summary>
    ///     Helper to copy whole directories.
    /// </summary>
    public static class CopyDir
    {
        public static void Copy(string sourceDirectory, string targetDirectory, bool verbose = false)
        {
            var diSource = new DirectoryInfo(sourceDirectory);
            var diTarget = new DirectoryInfo(targetDirectory);

            CopyAll(diSource, diTarget, verbose);
        }

        public static void CopyAll(DirectoryInfo source, DirectoryInfo target, bool verbose = false)
        {
            Directory.CreateDirectory(target.FullName);

            // Copy each file into the new directory.
            foreach (var fi in source.GetFiles())
            {
                if (verbose)
                    Protocol.Info($"Copying {fi.FullName}...");
                fi.CopyTo(Path.Combine(target.FullName, fi.Name), true);
            }

            // Copy each sub directory using recursion.
            foreach (var diSourceSubDir in source.GetDirectories())
            {
                var nextTargetSubDir = target.CreateSubdirectory(diSourceSubDir.Name);
                CopyAll(diSourceSubDir, nextTargetSubDir);
            }
        }
    }
}