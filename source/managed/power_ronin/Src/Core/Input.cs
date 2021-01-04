using System.Runtime.CompilerServices;
using PowerRonin.Mathematics;

namespace PowerRonin.Core
{
    /// <summary>
    ///     Contains methods for input fetching.
    /// </summary>
    public static class Input
    {
        private static Vector2 _mousePos = Vector2.Zero;

        /// <summary>
        ///     The mouse cursor position.
        /// </summary>
        public static Vector2 MousePosition => _mousePos;

        /// <summary>
        /// </summary>
        /// <param name="key">The key.</param>
        /// <returns>True if the key is currently pressed, else false.</returns>
        public static bool IsKeyDown(Key key)
        {
            return NativeRuntime.InputIsKeyDown(key);
        }

        /// <summary>
        /// </summary>
        /// <param name="mouseButton">The mouse button.</param>
        /// <returns>True if the mouse button is currently pressed, else false.</returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static bool IsMouseDown(MouseButton mouseButton)
        {
            return NativeRuntime.InputIsMouseDown(mouseButton);
        }

        internal static void Update()
        {
            NativeRuntime.InputGetCursorPosition(out var x, out var y);
            _mousePos.X = x;
            _mousePos.Y = y;
        }
    }
}