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
using System.Collections.Generic;
using System.Globalization;
using System.Reflection;
using Dreamcast.Json.Serialization;
#if !HAVE_LINQ
using Dreamcast.Json.Utilities.LinqBridge;

#else
using System.Linq;

#endif

namespace Dreamcast.Json.Utilities
{
    internal class ReflectionMember
    {
        public Type? MemberType { get; set; }
        public Serialization.Func<object, object?>? Getter { get; set; }
        public Serialization.Action<object, object?>? Setter { get; set; }
    }

    internal class ReflectionObject
    {
        private ReflectionObject(ObjectConstructor<object>? creator)
        {
            Members = new Dictionary<string, ReflectionMember>();
            Creator = creator;
        }

        public ObjectConstructor<object>? Creator { get; }
        public IDictionary<string, ReflectionMember> Members { get; }

        public object? GetValue(object target, string member)
        {
            var getter = Members[member].Getter!;
            return getter(target);
        }

        public void SetValue(object target, string member, object? value)
        {
            var setter = Members[member].Setter!;
            setter(target, value);
        }

        public Type GetType(string member)
        {
            return Members[member].MemberType!;
        }

        public static ReflectionObject Create(Type t, params string[] memberNames)
        {
            return Create(t, null, memberNames);
        }

        public static ReflectionObject Create(Type t, MethodBase? creator, params string[] memberNames)
        {
            var delegateFactory = JsonTypeReflector.ReflectionDelegateFactory;

            ObjectConstructor<object>? creatorConstructor = null;
            if (creator != null)
            {
                creatorConstructor = delegateFactory.CreateParameterizedConstructor(creator);
            }
            else
            {
                if (ReflectionUtils.HasDefaultConstructor(t, false))
                {
                    var ctor = delegateFactory.CreateDefaultConstructor<object>(t);

                    creatorConstructor = args => ctor();
                }
            }

            var d = new ReflectionObject(creatorConstructor);

            foreach (var memberName in memberNames)
            {
                var members = t.GetMember(memberName, BindingFlags.Instance | BindingFlags.Public);
                if (members.Length != 1) throw new ArgumentException("Expected a single member with the name '{0}'.".FormatWith(CultureInfo.InvariantCulture, memberName));

                var member = members.Single();

                var reflectionMember = new ReflectionMember();

                switch (member.MemberType())
                {
                    case MemberTypes.Field:
                    case MemberTypes.Property:
                        if (ReflectionUtils.CanReadMemberValue(member, false)) reflectionMember.Getter = delegateFactory.CreateGet<object>(member);

                        if (ReflectionUtils.CanSetMemberValue(member, false, false)) reflectionMember.Setter = delegateFactory.CreateSet<object>(member);
                        break;
                    case MemberTypes.Method:
                        var method = (MethodInfo) member;
                        if (method.IsPublic)
                        {
                            var parameters = method.GetParameters();
                            if (parameters.Length == 0 && method.ReturnType != typeof(void))
                            {
                                var call = delegateFactory.CreateMethodCall<object>(method);
                                reflectionMember.Getter = target => call(target);
                            }
                            else if (parameters.Length == 1 && method.ReturnType == typeof(void))
                            {
                                var call = delegateFactory.CreateMethodCall<object>(method);
                                reflectionMember.Setter = (target, arg) => call(target, arg);
                            }
                        }

                        break;
                    default:
                        throw new ArgumentException("Unexpected member type '{0}' for member '{1}'.".FormatWith(CultureInfo.InvariantCulture, member.MemberType(), member.Name));
                }

                reflectionMember.MemberType = ReflectionUtils.GetMemberUnderlyingType(member);

                d.Members[memberName] = reflectionMember;
            }

            return d;
        }
    }
}