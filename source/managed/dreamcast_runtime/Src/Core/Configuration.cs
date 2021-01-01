using System;
using System.Collections.Generic;
using System.IO;
using Dreamcast.Mathematics;

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
        ///     The name of the directory where configs are saved in.
        /// </summary>
        public const string ConfigDirectory = "config";

        /// <summary>
        ///     Display config.
        /// </summary>
        public DisplayConfiguration Display { get; set; } = new();

        /// <summary>
        ///     System overlay config.
        /// </summary>
        public OverlayConfiguration Overlay { get; set; } = new();

        /// <summary>
        ///     Graphics config.
        /// </summary>
        public GraphicsConfiguration Graphics { get; set; } = new();

        /// <summary>
        ///     Current global system config.
        /// </summary>
        public static Configuration Current { get; set; } = new();

        /// <summary>
        ///     Serializes all configs into their files.
        /// </summary>
        public static void Serialize()
        {
            try
            {
                if (!Directory.Exists(ConfigDirectory))
                    Directory.CreateDirectory(ConfigDirectory);
                Serializer.SerializeToJsonFile(Current.Display, DisplayConfiguration.FilePath);
                Serializer.SerializeToJsonFile(Current.Overlay, OverlayConfiguration.FilePath);
                Serializer.SerializeToJsonFile(Current.Graphics, GraphicsConfiguration.FilePath);
            }
            catch (Exception ex)
            {
                Protocol.Error("Failed to serialize config: " + ex);
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
                Current.Display =
                    Serializer.DeserializeFromJsonFile<DisplayConfiguration>(DisplayConfiguration.FilePath);
                Current.Overlay =
                    Serializer.DeserializeFromJsonFile<OverlayConfiguration>(OverlayConfiguration.FilePath);
                Current.Graphics =
                    Serializer.DeserializeFromJsonFile<GraphicsConfiguration>(GraphicsConfiguration.FilePath);
            }
            catch (Exception ex)
            {
                Protocol.Error("Failed to deserialize config: " + ex);
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
                Display_WindowWidth = (ushort) Current.Display.Resolution.Width,
                Display_WindowHeight = (ushort) Current.Display.Resolution.Height,
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

            public Size2 Resolution { get; set; } = new(1920, 1080);

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

            public Dictionary<BuildTarget, GraphicsAPI[]> GraphicBackends { get; set; } = new()
            {
                {
                    BuildTarget.StandaloneWindows,
                    new[] {GraphicsAPI.Direct3D11, GraphicsAPI.Direct3D12, GraphicsAPI.Vulkan, GraphicsAPI.OpenGL}
                },
                {BuildTarget.StandaloneLinux, new[] {GraphicsAPI.OpenGL, GraphicsAPI.Vulkan}},
                {BuildTarget.StandaloneMac, new[] {GraphicsAPI.Metal, GraphicsAPI.OpenGL, GraphicsAPI.Vulkan} }
            };

            public MsaaMode MSAAMode { get; set; } = MsaaMode.X4;

            public bool EnableHighDPIMode { get; set; } = false;

            public bool EnableSRGBBackbuffer { get; set; } = true;

            public bool EnableHDR10 { get; set; } = false;

            public bool EnableMaxAnisotropy { get; set; } = false;
        }
    }
}