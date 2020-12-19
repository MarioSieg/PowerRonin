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
using System.IO;
using System.Runtime.InteropServices;
using Dreamcast.Core;

namespace Dreamcast.Tools
{
    internal static class Builder
    {
        private const string BuildOutputDir = "out/build";
        private const string BuildDirMsvc = "x64-Release";
        private const string BuildDirClang = "x64-Clang-Release";
        private const string OutputDirMain = "engine/core/bin";

        private const string WindowsOnlyDir = "windows";
        private const string LinuxOnlyDir = "linux";
        private static readonly string ExeFileName = RuntimeInformation.IsOSPlatform(OSPlatform.Linux) ? "dreamcast" : "dreamcast.exe";

        private static readonly string[] RequiredDirs = {"audio", "fonts", "meshes", "shaders", "textures", "examples", "runtime"};

        public static void BuildEditorStandalone(string outputDir = "retail")
        {
            try
            {
                Protocol.Critical("Build started! Output dir: " + outputDir);
                var buildDirClang = Path.Combine(BuildOutputDir, BuildDirClang);
                var buildDirMsvc = Path.Combine(BuildOutputDir, BuildDirMsvc);
                if (!Directory.Exists(buildDirClang) && !Directory.Exists(buildDirMsvc))
                {
                    Protocol.Error("Missing build directories! Requires either Clang or MSVC output directory!");
                    Protocol.Error("Clang: " + buildDirClang);
                    Protocol.Error("MSVC: " + buildDirMsvc);
                    return;
                }

                var buildDir = Directory.Exists(buildDirClang) ? buildDirClang : buildDirMsvc;
                if (!Directory.Exists(buildDir))
                {
                    Protocol.Error("Invalid build dir: " + buildDir);
                    return;
                }

                var exe = Path.Combine(buildDir, ExeFileName);
                if (!File.Exists(exe))
                {
                    Protocol.Error("Missing engine executable: " + exe);
                    return;
                }

                if (Directory.Exists(outputDir)) Directory.Delete(outputDir, true);

                Directory.CreateDirectory(outputDir);
                Directory.CreateDirectory(Path.Combine(outputDir, OutputDirMain));

                File.Copy(exe, Path.Combine(outputDir, OutputDirMain, ExeFileName));

                foreach (var dir in RequiredDirs)
                {
                    if (!Directory.Exists(dir))
                    {
                        Protocol.Error("Missing directory in root: " + dir);
                        return;
                    }

                    CopyDir.Copy(dir, Path.Combine(outputDir, dir));
                }

                if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
                {
                    if (!Directory.Exists(LinuxOnlyDir))
                    {
                        Protocol.Error("Missing Linux specific dir: " + LinuxOnlyDir);
                        return;
                    }

                    foreach (var file in Directory.GetFiles(LinuxOnlyDir, "*.so"))
                        File.Copy(file, Path.Combine(outputDir, OutputDirMain, Path.GetFileName(file)));
                }
                else
                {
                    if (!Directory.Exists(WindowsOnlyDir))
                    {
                        Protocol.Error("Missing Windows specific dir: " + WindowsOnlyDir);
                        return;
                    }

                    foreach (var file in Directory.GetFiles(WindowsOnlyDir, "*.dll"))
                        File.Copy(file, Path.Combine(outputDir, OutputDirMain, Path.GetFileName(file)));
                }

                Protocol.Info("Done! Check: " + outputDir);
            }
            catch (Exception exception)
            {
                Protocol.Error("Failed to build: " + exception.Message);
            }
        }
    }
}