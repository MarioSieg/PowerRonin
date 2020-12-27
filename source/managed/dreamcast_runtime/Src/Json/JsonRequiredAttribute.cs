using System;

namespace Dreamcast.Json
{
    /// <summary>
    ///     Instructs the <see cref="JsonSerializer" /> to always serialize the member, and to require that the member has a
    ///     value.
    /// </summary>
    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property)]
    public sealed class JsonRequiredAttribute : Attribute
    {
    }
}