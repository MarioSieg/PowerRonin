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

using System.Runtime.CompilerServices;
using Dreamcast.Mathematics;

namespace Dreamcast.Core
{
    /// <summary>
    ///     Contains methods for input fetching.
    /// </summary>
    public static class Input
    {
        private static Vector2 CursorPos = Vector2.Zero;

        /// <summary>
        ///     The mouse cursor position.
        /// </summary>
        public static Vector2 CursorPosition => CursorPos;

        /// <summary>
        /// </summary>
        /// <param name="key">The key.</param>
        /// <returns>True if the key is currently pressed, else false.</returns>
        [NativeRuntimeCall]
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool IsKeyDown(Key key);

        /// <summary>
        /// </summary>
        /// <param name="mouseButton">The mouse button.</param>
        /// <returns>True if the mouse button is currently pressed, else false.</returns>
        [NativeRuntimeCall]
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool IsMouseDown(MouseButton mouseButton);

        [NativeRuntimeCall]
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetCursorPosition(out float x, out float y);

        internal static void UpdateMouseCursor()
        {
            GetCursorPosition(out var x, out var y);
            CursorPos.X = x;
            CursorPos.Y = y;
        }
    }
}