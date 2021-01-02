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
        public EditorConfiguration Editor { get; set; } = new();

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
                Serializer.SerializeToJsonFile(Current.Editor, EditorConfiguration.FilePath);
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
                Current.Editor =
                    Serializer.DeserializeFromJsonFile<EditorConfiguration>(EditorConfiguration.FilePath);
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
                Overlay_FontSize = Current.Editor.FontSize,
                Overlay_EnableFontAntialiasing = Current.Editor.EnableFontAntialiasing,
                Overlay_Alpha = Current.Editor.Alpha,
                Overlay_Rounding = Current.Editor.Rounding,
                Overlay_ShowTerminal = Current.Editor.ShowTerminal,
                Overlay_ShowStats = Current.Editor.ShowStats,
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

            public bool VSync { get; set; } = true;

            public ushort MaxFrameRate { get; set; } = 300;
        }

        public sealed class EditorConfiguration
        {
            public static string FilePath { get; set; } = Path.Combine(ConfigDirectory, "editor.ini");

            public byte FontSize { get; set; } = 24;

            public byte AutoFontSizeForFHD { get; set; } = 14;

            public byte AutoFontSizeForWQHD { get; set; } = 18;

            public byte AutoFontSizeForUHD4K { get; set; } = 22;
            
            public bool AutoSetFontSize { get; set; } = true;

            public bool EnableFontAntialiasing { get; set; } = true;

            public float Alpha { get; set; } = 1.0f;

            public float Rounding { get; set; } = 4.0f;

            public bool ShowTerminal { get; set; } = true;

            public bool ShowStats { get; set; } = true;

            public bool ShowMatrixStats { get; set; } = true;

            public byte StatsTextColor { get; set; } = 0xF;

            public bool ShowBigStats { get; set; } = false;

            public float GridSize { get; set; } = 10.0f;

            public Vector3 GridOriginCenter { get; set; } = Vector3.Zero;

            public bool EnableGizmos { get; set; } = true;
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

            public MsaaMode MSAAMode { get; set; } = MsaaMode.Off;

            public bool EnableHighDPIMode { get; set; } = false;

            public bool EnableSRGBBackbuffer { get; set; } = true;

            public bool EnableHDR10 { get; set; } = false;

            public bool EnableMaxAnisotropy { get; set; } = false;
        }
    }
}