using System.IO;
using System.Runtime.InteropServices;

namespace Dreamcast.Core
{
    [StructLayout(LayoutKind.Sequential)]
    public struct GraphicsConfig
    {
        [field: MarshalAs(UnmanagedType.U1)] public GraphicsApi GraphicsApi { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public MsaaMode MSAAMode { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool EnableHighDPIMode { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool EnableSRGBBackbuffer { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool EnableHDR10 { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool EnableMaxAnisotropy { get; set; }

        public static string FilePath { get; set; } = Path.Combine(Config.ConfigDirectory, "graphics.ini");

        /// <summary>
        ///     Applies the instance.
        /// </summary>
        public void Apply()
        {
            NativeRuntime.CfgApplyGraphics(this);
        }
    }
}