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

using System.Runtime.InteropServices;

namespace Dreamcast.Core
{
    /// <summary>
    ///     !! Maps to NativeConfig in source/scripting/native_config.hpp !!
    ///     !! Warning! None of these methods should be changed because are mapped to native functions !!
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    internal struct NativeConfig
    {
        [MarshalAs(UnmanagedType.U1)] public bool Display_IsWindowFullscreen;
        [MarshalAs(UnmanagedType.U1)] public bool Display_IsWindowMaximized;
        [MarshalAs(UnmanagedType.U2)] public ushort Display_WindowWidth;
        [MarshalAs(UnmanagedType.U2)] public ushort Display_WindowHeight;
        [MarshalAs(UnmanagedType.U1)] public bool Display_VSync;
        [MarshalAs(UnmanagedType.U2)] public ushort Display_MaxFrameRate;

        [MarshalAs(UnmanagedType.U1)] public byte Overlay_FontSize;
        [MarshalAs(UnmanagedType.U1)] public byte Overlay_Theme;
        [MarshalAs(UnmanagedType.U1)] public bool Overlay_EnableFontAntialiasing;
        [MarshalAs(UnmanagedType.R4)] public float Overlay_Alpha;
        [MarshalAs(UnmanagedType.R4)] public float Overlay_Rounding;
        [MarshalAs(UnmanagedType.U1)] public bool Overlay_ShowTerminal;
        [MarshalAs(UnmanagedType.U1)] public bool Overlay_ShowStats;

        [MarshalAs(UnmanagedType.U1)] public byte Graphics_MSAAMode;
        [MarshalAs(UnmanagedType.U1)] public bool Graphics_EnableHighDPIMode;
        [MarshalAs(UnmanagedType.U1)] public bool Graphics_EnableSRGBBackbuffer;
        [MarshalAs(UnmanagedType.U1)] public bool Graphics_EnableHDR10;
        [MarshalAs(UnmanagedType.U1)] public bool Graphics_EnableMaxAnisotropy;
    }
}