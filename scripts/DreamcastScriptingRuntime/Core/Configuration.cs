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
using System.Collections.Generic;
using System.IO;

#nullable enable

namespace Dreamcast.Core
{
    public enum ConfigApplyFlags : byte
    {
        None = 0,
        Display = 1 << 0,
        Overlay = 1 << 1,
        Graphics = 1 << 2,
        All = byte.MaxValue
    }

    /// <summary>
    ///     Contains all configuration variables.
    /// </summary>
    public sealed class Configuration
    {
        /// <summary>
        ///     Display config.
        /// </summary>
        public DisplayConfiguration Display { get; set; } = new DisplayConfiguration();

        /// <summary>
        ///     System overlay config.
        /// </summary>
        public OverlayConfiguration Overlay { get; set; } = new OverlayConfiguration();

        /// <summary>
        ///     Graphics config.
        /// </summary>
        public GraphicsConfiguration Graphics { get; set; } = new GraphicsConfiguration();

        /// <summary>
        ///     Current global system config.
        /// </summary>
        public static Configuration Current { get; set; } = new Configuration();

        /// <summary>
        ///     The name of the directory where configs are saved in.
        /// </summary>
        public static string ConfigDirectory => "config";

        /// <summary>
        ///     Serializes all configs into their files.
        /// </summary>
        public static void Serialize()
        {
            try
            {
                if (!Directory.Exists(ConfigDirectory))
                    Directory.CreateDirectory(ConfigDirectory);
                Serializer<DisplayConfiguration>.SerializeToXmlFile(Current.Display, DisplayConfiguration.FilePath);
                Serializer<OverlayConfiguration>.SerializeToXmlFile(Current.Overlay, OverlayConfiguration.FilePath);
                Serializer<GraphicsConfiguration>.SerializeToXmlFile(Current.Graphics, GraphicsConfiguration.FilePath);
            }
            catch (Exception e)
            {
                Protocol.Error("Failed to serialize config: " + e.Message);
            }
        }

        /// <summary>
        ///     Deserializes all configs from their files.
        /// </summary>
        public static void Deserialize()
        {
            if (!Directory.Exists(ConfigDirectory))
            {
                Serialize();
                return;
            }

            try
            {
                Current.Display = Serializer<DisplayConfiguration>.DeserializeFromXmlFile(DisplayConfiguration.FilePath);
                Current.Overlay = Serializer<OverlayConfiguration>.DeserializeFromXmlFile(OverlayConfiguration.FilePath);
                Current.Graphics = Serializer<GraphicsConfiguration>.DeserializeFromXmlFile(GraphicsConfiguration.FilePath);
                Protocol.Info("Deserialized all configs!");
            }
            catch (Exception)
            {
                Protocol.Warn("Failed to deserialize config!");
                Serialize();
                Protocol.Info("Serialized default config.");
            }
        }

        /// <summary>
        ///     Applies all configs.
        ///     This might take some time as some settings
        ///     require some internal reloads.
        /// </summary>
        public void Apply(ConfigApplyFlags flags = ConfigApplyFlags.All)
        {
            var nativeConfig = new NativeConfig
            {
                Display_IsWindowFullscreen = Current.Display.IsWindowFullscreen,
                Display_IsWindowMaximized = Current.Display.IsWindowMaximized,
                Display_WindowWidth = Current.Display.WindowWidth,
                Display_WindowHeight = Current.Display.WindowHeight,
                Display_VSync = Current.Display.VSync,
                Display_MaxFrameRate = Current.Display.MaxFrameRate,
                Overlay_FontSize = Current.Overlay.FontSize,
                Overlay_Theme = (byte) Current.Overlay.Theme,
                Overlay_EnableFontAntialiasing = Current.Overlay.EnableFontAntialiasing,
                Overlay_Alpha = Current.Overlay.Alpha,
                Overlay_Rounding = Current.Overlay.Rounding,
                Overlay_ShowTerminal = Current.Overlay.ShowTerminal,
                Overlay_ShowStats = Current.Overlay.ShowStats,
                Graphics_MSAAMode = (byte) Current.Graphics.MSAAMode,
                Graphics_EnableHighDPIMode = Current.Graphics.EnableHighDPIMode,
                Graphics_EnableSRGBBackbuffer = Current.Graphics.EnableSRGBBackbuffer,
                Graphics_EnableHDR10 = Current.Graphics.EnableHDR10,
                Graphics_EnableMaxAnisotropy = Current.Graphics.EnableMaxAnisotropy
            };
            NativeRuntime.CfgSetNative(in nativeConfig, flags);
        }

        /// <summary>
        ///     Contains display config.
        /// </summary>
        public sealed class DisplayConfiguration
        {
            /// <summary>
            ///     The config file path.
            /// </summary>
            public static string FilePath { get; set; } = Path.Combine(ConfigDirectory, "display.ini");

            public bool IsWindowFullscreen { get; set; } = false;

            public bool IsWindowMaximized { get; set; } = true;

            public ushort WindowWidth { get; set; } = 1920;

            public ushort WindowHeight { get; set; } = 1080;

            public bool VSync { get; set; } = false;

            public ushort MaxFrameRate { get; set; } = 300;
        }

        public sealed class OverlayConfiguration
        {
            public static string FilePath { get; set; } = Path.Combine(ConfigDirectory, "overlay.ini");

            public byte FontSize { get; set; } = 24;

            public SystemOverlayTheme Theme { get; set; } = SystemOverlayTheme.Dark;

            public bool EnableFontAntialiasing { get; set; } = true;

            public float Alpha { get; set; } = 1.0f;

            public float Rounding { get; set; } = 4.0f;

            public bool ShowTerminal { get; set; } = true;

            public bool ShowStats { get; set; } = true;
        }

        public sealed class GraphicsConfiguration
        {
            public static string FilePath { get; set; } = Path.Combine(ConfigDirectory, "graphics.ini");

            public Dictionary<BuildTarget, GraphicsAPI[]> GraphicBackends { get; set; } = new Dictionary<BuildTarget, GraphicsAPI[]> {{BuildTarget.StandaloneWindows, new[] {GraphicsAPI.Direct3D11, GraphicsAPI.Direct3D12, GraphicsAPI.Vulkan, GraphicsAPI.OpenGL}}, {BuildTarget.StandaloneLinux, new[] {GraphicsAPI.OpenGL, GraphicsAPI.Vulkan}}, {BuildTarget.StandaloneMac, new[] {GraphicsAPI.Metal, GraphicsAPI.OpenGL}}};

            public MSAAMode MSAAMode { get; set; } = MSAAMode.X16;

            public bool EnableHighDPIMode { get; set; } = false;

            public bool EnableSRGBBackbuffer { get; set; } = true;

            public bool EnableHDR10 { get; set; } = false;

            public bool EnableMaxAnisotropy { get; set; } = true;
        }
    }
}