using System;

namespace PowerRonin.Core
{
    [AttributeUsage(AttributeTargets.Method)]
    internal sealed class CalledFromNativeRuntime : Attribute
    {
    }
}