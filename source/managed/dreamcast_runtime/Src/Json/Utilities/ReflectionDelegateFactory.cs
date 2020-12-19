// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

using System;
using System.Globalization;
using System.Reflection;
using Dreamcast.Json.Serialization;
#if !HAVE_LINQ

#endif

namespace Dreamcast.Json.Utilities
{
    internal abstract class ReflectionDelegateFactory
    {
        public Serialization.Func<T, object?> CreateGet<T>(MemberInfo memberInfo)
        {
            if (memberInfo is PropertyInfo propertyInfo)
            {
                // https://github.com/dotnet/corefx/issues/26053
                if (propertyInfo.PropertyType.IsByRef) throw new InvalidOperationException("Could not create getter for {0}. ByRef return values are not supported.".FormatWith(CultureInfo.InvariantCulture, propertyInfo));

                return CreateGet<T>(propertyInfo);
            }

            if (memberInfo is FieldInfo fieldInfo) return CreateGet<T>(fieldInfo);

            throw new Exception("Could not create getter for {0}.".FormatWith(CultureInfo.InvariantCulture, memberInfo));
        }

        public Serialization.Action<T, object?> CreateSet<T>(MemberInfo memberInfo)
        {
            if (memberInfo is PropertyInfo propertyInfo) return CreateSet<T>(propertyInfo);

            if (memberInfo is FieldInfo fieldInfo) return CreateSet<T>(fieldInfo);

            throw new Exception("Could not create setter for {0}.".FormatWith(CultureInfo.InvariantCulture, memberInfo));
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