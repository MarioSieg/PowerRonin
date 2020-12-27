using System;

namespace Dreamcast.Core
{
    [AttributeUsage(AttributeTargets.Method)]
    internal sealed class CallToNativeRuntime : Attribute
    {
    }
}