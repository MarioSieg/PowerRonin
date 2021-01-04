using System.Runtime.CompilerServices;

namespace PowerRonin.Core
{
    /// <summary>
    ///     Contains all internal calls.
    ///     Warning! None of these methods should be changed because
    ///     they are mapped to native functions.
    /// </summary>
    public static class NativeRuntime
    {
        [CallToNativeRuntime]
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void ProtocolLog(LogLevel level, string message);

        [CallToNativeRuntime]
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void ProtocolFlush();

        [CallToNativeRuntime]
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void ProtocolSetFormatPattern(string pattern);

        [CallToNativeRuntime]
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool InputIsKeyDown(Key key);

        [CallToNativeRuntime]
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void InputGetCursorPosition(out float x, out float y);

        [CallToNativeRuntime]
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool InputIsMouseDown(MouseButton mouseButton);

        [CallToNativeRuntime]
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void CfgApplyDisplay(in DisplayConfig cfg);

        [CallToNativeRuntime]
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void CfgApplyEditor(in EditorConfig cfg);

        [CallToNativeRuntime]
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void CfgApplyGraphics(in GraphicsConfig cfg);
    }
}