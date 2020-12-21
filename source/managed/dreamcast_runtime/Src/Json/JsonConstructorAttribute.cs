using System;

namespace Dreamcast.Json
{
    /// <summary>
    ///     Instructs the <see cref="JsonSerializer" /> to use the specified constructor when deserializing that object.
    /// </summary>
    [AttributeUsage(AttributeTargets.Constructor)]
    public sealed class JsonConstructorAttribute : Attribute
    {
    }
}