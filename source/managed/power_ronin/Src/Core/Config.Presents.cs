using PowerRonin.Mathematics;

namespace PowerRonin.Core
{
    public sealed partial class Config
    {
        public static readonly Config DefaultLowestSettings = new()
        {
            Display = new DisplayConfig
            {
                FullscreenMode = true,
                MaximizeWindow = false,
                MaxFrameRate = 0,
                Resolution = new Size2(1920, 1090),
                VSync = true
            },
            Editor = new EditorConfig
            {
                Alpha = 1.0f,
                AutoFontSizeForFHD = 18,
                AutoFontSizeForWQHD = 20,
                AutoFontSizeForUHD4K = 22,
                AutoSetFontSize = true,
                EnableFontAntialiasing = true,
                EnableGizmos = true,
                CustomFontSize = 20,
                GridOriginCenter = Vector3.Zero,
                GridSize = 100.0f,
                ShowBigStats = false,
                ShowGrid = true,
                ShowMatrixStats = true,
                ShowStats = true,
                ShowTerminal = false,
                StatsTextColor = 0xF
            },
            Graphics = new GraphicsConfig
            {
                EnableHDR10 = false,
                EnableHighDPIMode = false,
                EnableMaxAnisotropy = false,
                EnableSRGBBackbuffer = true,
                GraphicsApi = Helper.SmartDetermineGraphicsApi(),
                MSAAMode = MsaaMode.Off
            }
        };

        public static readonly Config DefaultMaxSettings = new()
        {
            Display = new DisplayConfig
            {
                FullscreenMode = true,
                MaximizeWindow = false,
                MaxFrameRate = 0,
                Resolution = new Size2(1920, 1090),
                VSync = true
            },
            Editor = new EditorConfig
            {
                Alpha = 1.0f,
                AutoFontSizeForFHD = 18,
                AutoFontSizeForWQHD = 20,
                AutoFontSizeForUHD4K = 22,
                AutoSetFontSize = true,
                EnableFontAntialiasing = true,
                EnableGizmos = true,
                CustomFontSize = 20,
                GridOriginCenter = Vector3.Zero,
                GridSize = 100.0f,
                ShowBigStats = false,
                ShowGrid = true,
                ShowMatrixStats = true,
                ShowStats = true,
                ShowTerminal = true,
                StatsTextColor = 0xF
            },
            Graphics = new GraphicsConfig
            {
                EnableHDR10 = false,
                EnableHighDPIMode = false,
                EnableMaxAnisotropy = true,
                EnableSRGBBackbuffer = true,
                GraphicsApi = Helper.SmartDetermineGraphicsApi(),
                MSAAMode = MsaaMode.X16
            }
        };

        public static readonly Config DefaultSafeMode = new()
        {
            Display = new DisplayConfig
            {
                FullscreenMode = false,
                MaximizeWindow = false,
                MaxFrameRate = 0,
                Resolution = new Size2(800, 600),
                VSync = true
            },
            Editor = new EditorConfig
            {
                Alpha = 1.0f,
                AutoFontSizeForFHD = 18,
                AutoFontSizeForWQHD = 20,
                AutoFontSizeForUHD4K = 22,
                AutoSetFontSize = true,
                EnableFontAntialiasing = true,
                EnableGizmos = true,
                CustomFontSize = 20,
                GridOriginCenter = Vector3.Zero,
                GridSize = 100.0f,
                ShowBigStats = false,
                ShowGrid = true,
                ShowMatrixStats = true,
                ShowStats = true,
                ShowTerminal = true,
                StatsTextColor = 0xF
            },
            Graphics = new GraphicsConfig
            {
                EnableHDR10 = false,
                EnableHighDPIMode = false,
                EnableMaxAnisotropy = false,
                EnableSRGBBackbuffer = true,
                GraphicsApi = Helper.SmartDetermineGraphicsApi(),
                MSAAMode = MsaaMode.Off
            }
        };

        public static readonly Config DefaultEditorSettings = new()
        {
            Display = new DisplayConfig
            {
                FullscreenMode = false,
                MaximizeWindow = true,
                MaxFrameRate = 0,
                Resolution = new Size2(1920, 1090),
                VSync = false
            },
            Editor = new EditorConfig
            {
                Alpha = 1.0f,
                AutoFontSizeForFHD = 18,
                AutoFontSizeForWQHD = 20,
                AutoFontSizeForUHD4K = 22,
                AutoSetFontSize = true,
                EnableFontAntialiasing = true,
                EnableGizmos = true,
                CustomFontSize = 20,
                GridOriginCenter = Vector3.Zero,
                GridSize = 10.0f,
                ShowBigStats = true,
                ShowGrid = false,
                ShowMatrixStats = true,
                ShowStats = true,
                ShowTerminal = true,
                StatsTextColor = 0xF
            },
            Graphics = new GraphicsConfig
            {
                EnableHDR10 = false,
                EnableHighDPIMode = false,
                EnableMaxAnisotropy = false,
                EnableSRGBBackbuffer = true,
                GraphicsApi = Helper.SmartDetermineGraphicsApi(),
                MSAAMode = MsaaMode.X16
            }
        };

        /// <summary>
        ///     Current global system config.
        /// </summary>
        public static Config Current { get; set; } = DefaultEditorSettings;
    }
}