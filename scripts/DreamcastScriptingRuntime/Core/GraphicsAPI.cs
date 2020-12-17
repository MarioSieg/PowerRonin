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

namespace Dreamcast.Core
{
    /// <summary>
    ///     Contains all supported graphics APIs.
    /// </summary>
    public enum GraphicsAPI
    {
        /// <summary>
        ///     Windows only.
        /// </summary>
        Direct3D11,

        /// <summary>
        ///     Windows only.
        /// </summary>
        Direct3D12,

        /// <summary>
        ///     Mac only.
        /// </summary>
        Metal,

        /// <summary>
        ///     Cross platform.
        /// </summary>
        Vulkan,

        /// <summary>
        ///     Cross platform.
        /// </summary>
        OpenGL
    }
}