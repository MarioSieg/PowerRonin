using System;
using PowerRonin.Json.Utilities;

namespace PowerRonin.Json.Serialization
{
    internal static class CachedAttributeGetter<T> where T : Attribute
    {
        private static readonly ThreadSafeStore<object, T?> TypeAttributeCache = new(JsonTypeReflector.GetAttribute<T>);

        public static T? GetAttribute(object type)
        {
            return TypeAttributeCache.Get(type);
        }
    }
}