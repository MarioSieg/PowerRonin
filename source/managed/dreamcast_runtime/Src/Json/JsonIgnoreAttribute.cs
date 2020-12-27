using System;

namespace Dreamcast.Json
{
    /// <summary>
    ///     Instructs the <see cref="JsonSerializer" /> not to serialize the public field or public read/write property value.
    /// </summary>
    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property)]
    public sealed class JsonIgnoreAttribute : Attribute
    {
    }
}