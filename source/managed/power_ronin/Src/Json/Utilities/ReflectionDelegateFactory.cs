using System;
using System.Globalization;
using System.Reflection;
using PowerRonin.Json.Serialization;

#if !HAVE_LINQ

#endif

namespace PowerRonin.Json.Utilities
{
    internal abstract class ReflectionDelegateFactory
    {
        public Serialization.Func<T, object?> CreateGet<T>(MemberInfo memberInfo)
        {
            if (memberInfo is PropertyInfo propertyInfo)
            {
                // https://github.com/dotnet/corefx/issues/26053
                if (propertyInfo.PropertyType.IsByRef)
                    throw new InvalidOperationException(
                        "Could not create getter for {0}. ByRef return values are not supported.".FormatWith(
                            CultureInfo.InvariantCulture, propertyInfo));

                return CreateGet<T>(propertyInfo);
            }

            if (memberInfo is FieldInfo fieldInfo) return CreateGet<T>(fieldInfo);

            throw new Exception(
                "Could not create getter for {0}.".FormatWith(CultureInfo.InvariantCulture, memberInfo));
        }

        public Serialization.Action<T, object?> CreateSet<T>(MemberInfo memberInfo)
        {
            if (memberInfo is PropertyInfo propertyInfo) return CreateSet<T>(propertyInfo);

            if (memberInfo is FieldInfo fieldInfo) return CreateSet<T>(fieldInfo);

            throw new Exception(
                "Could not create setter for {0}.".FormatWith(CultureInfo.InvariantCulture, memberInfo));
        }

        public abstract MethodCall<T, object?> CreateMethodCall<T>(MethodBase method);
        public abstract ObjectConstructor<object> CreateParameterizedConstructor(MethodBase method);
        public abstract Serialization.Func<T> CreateDefaultConstructor<T>(Type type);
        public abstract Serialization.Func<T, object?> CreateGet<T>(PropertyInfo propertyInfo);
        public abstract Serialization.Func<T, object?> CreateGet<T>(FieldInfo fieldInfo);
        public abstract Serialization.Action<T, object?> CreateSet<T>(FieldInfo fieldInfo);
        public abstract Serialization.Action<T, object?> CreateSet<T>(PropertyInfo propertyInfo);
    }
}