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

#nullable enable

namespace Dreamcast.Core
{
    /// <summary>
    ///     Contains all configuration variables.
    /// </summary>
    public sealed class Configuration
    {
        public DisplayConfiguration Display { get; set; } = new DisplayConfiguration();

        public OverlayConfiguration Overlay { get; set; } = new OverlayConfiguration();

        public static Configuration Current { get; set; } = new Configuration();

        public static string FilePath { get; set; } = "config/system.ini";

        public void Apply()
        {
            Display.Apply();
        }

        public static void LoadCurrent(bool createIfNotExist = true)
        {
            try
            {
                var directory = Path.GetDirectoryName(FilePath);
                if (createIfNotExist && directory != null && !File.Exists(FilePath))
                {
                    Directory.CreateDirectory(directory);
                    SaveCurrent();
                    return;
                }

                Current = Serializer<Configuration>.DeserializeFromXmlFile(FilePath);

                Current.Apply();
            }
            catch (Exception)
            {
                Protocol.Info("Failed to load config from file: " + FilePath);
                try
                {
                    SaveCurrent();
                    Protocol.Info("Created default config file!");
                }
                catch (Exception)
                {
                }
            }
        }

        public static void SaveCurrent()
        {
            Serializer<Configuration>.SerializeToXmlFile(Current, FilePath);
        }

        public sealed class DisplayConfiguration
        {
            public bool IsWindowFullscreen { get; set; } = false;

            public bool IsWindowMaximized { get; set; } = true;

            public ushort WindowWidth { get; set; } = 1920;

            public ushort WindowHeight { get; set; } = 1080;

            public void Apply()
            {
                NativeRuntime.CfgSetWindowFullscreen(IsWindowFullscreen);
            }
        }

        public sealed class OverlayConfiguration
        {
            public byte FontSize { get; set; } = 24;

            public bool EnableAntialising { get; set; } = true;

            public float Alpha { get; set; } = 1.0f;

            public float Rounding { get; set; } = 4.0f;

            public bool ShowTerminal { get; set; } = true;

            public bool ShowStats { get; set; } = true;
        }
    }
}