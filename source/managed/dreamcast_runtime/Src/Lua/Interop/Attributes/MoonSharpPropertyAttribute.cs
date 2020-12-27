using System;

namespace Dreamcast.Lua.Interpreter
{
    /// <summary>
    ///     Marks a property as a configruation property
    /// </summary>
    [AttributeUsage(AttributeTargets.Property, AllowMultiple = true)]
    public sealed class LuaPropertyAttribute : Attribute
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="LuaPropertyAttribute" /> class.
        /// </summary>
        public LuaPropertyAttribute()
        {
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="LuaPropertyAttribute" /> class.
        /// </summary>
        /// <param name="name">The name for this property</param>
        public LuaPropertyAttribute(string name)
        {
            Name = name;
        }

        /// <summary>
        ///     The metamethod name (like '__div', '__ipairs', etc.)
        /// </summary>
        public string Name { get; }
    }
}