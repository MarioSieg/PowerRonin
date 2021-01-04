using System;

namespace PowerRonin.Lua.Interpreter
{
    /// <summary>
    ///     Marks a type of automatic registration as userdata (which happens only if UserData.RegisterAssembly is called).
    /// </summary>
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct, Inherited = false)]
    public sealed class LuaUserDataAttribute : Attribute
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="LuaUserDataAttribute" /> class.
        /// </summary>
        public LuaUserDataAttribute()
        {
            AccessMode = InteropAccessMode.Default;
        }

        /// <summary>
        ///     The interop access mode
        /// </summary>
        public InteropAccessMode AccessMode { get; set; }
    }
}