using System;

namespace Dreamcast.Lua.Interpreter
{
    /// <summary>
    ///     Forces a class member visibility to scripts. Can be used to hide public members. Equivalent to
    ///     Dreamcast.LuaVisible(false).
    /// </summary>
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property | AttributeTargets.Field
                    | AttributeTargets.Constructor | AttributeTargets.Event)]
    public sealed class LuaHiddenAttribute : Attribute
    {
    }
}