using System;

namespace PowerRonin.Lua.Interpreter
{
    /// <summary>
    ///     Marks a method as the handler of metamethods of a userdata type
    /// </summary>
    [AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]
    public sealed class LuaUserDataMetamethodAttribute : Attribute
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="LuaUserDataMetamethodAttribute" /> class.
        /// </summary>
        /// <param name="name">The metamethod name (like '__div', '__ipairs', etc.)</param>
        public LuaUserDataMetamethodAttribute(string name)
        {
            Name = name;
        }

        /// <summary>
        ///     The metamethod name (like '__div', '__ipairs', etc.)
        /// </summary>
        public string Name { get; }
    }
}