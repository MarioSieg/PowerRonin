using System.IO;
using System.Runtime.InteropServices;
using Dreamcast.Mathematics;

namespace Dreamcast.Core
{
    [StructLayout(LayoutKind.Sequential)]
    [NativeHybridMapping("EditorConfig", "dce/config.hpp")]
    public struct EditorConfig
    {
        [field: MarshalAs(UnmanagedType.U1)] public byte CustomFontSize { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public byte AutoFontSizeForFHD { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public byte AutoFontSizeForWQHD { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public byte AutoFontSizeForUHD4K { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool AutoSetFontSize { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool EnableFontAntialiasing { get; set; }

        [field: MarshalAs(UnmanagedType.R4)] public float Alpha { get; set; }

        [field: MarshalAs(UnmanagedType.R4)] public float Rounding { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool ShowTerminal { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool ShowStats { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool ShowMatrixStats { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public byte StatsTextColor { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool ShowBigStats { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool ShowGrid { get; set; }

        [field: MarshalAs(UnmanagedType.R4)] public float GridSize { get; set; }

        public Vector3 GridOriginCenter { get; set; }

        [field: MarshalAs(UnmanagedType.U1)] public bool EnableGizmos { get; set; }

        public static string FilePath { get; set; } = Path.Combine(Config.ConfigDirectory, "editor.ini");

        /// <summary>
        ///     Applies the instance.
        /// </summary>
        public void Apply()
        {
            NativeRuntime.CfgApplyEditor(this);
        }
    }
}