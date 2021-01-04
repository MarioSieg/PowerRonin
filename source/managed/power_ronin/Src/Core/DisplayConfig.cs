using System.IO;
using System.Runtime.InteropServices;
using PowerRonin.Mathematics;

namespace PowerRonin.Core
{
    /// <summary>
    ///     Contains display config.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    [NativeHybridMapping("DisplayConfig", "dce/config.hpp")]
    public struct DisplayConfig
    {
        [field: MarshalAs(UnmanagedType.U1)] public bool FullscreenMode { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool MaximizeWindow { get; set; }

        public Size2 Resolution { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool VSync { get; set; }

        [field: MarshalAs(UnmanagedType.U2)] public ushort MaxFrameRate { get; set; }

        /// <summary>
        ///     The config file path.
        /// </summary>
        public static string FilePath { get; set; } = Path.Combine(Config.ConfigDirectory, "display.ini");

        /// <summary>
        ///     Applies the instance.
        /// </summary>
        public void Apply()
        {
            NativeRuntime.CfgApplyDisplay(this);
        }
    }
}