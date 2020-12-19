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
using MoonSharp.Interpreter.Interop.BasicDescriptors;
using MoonSharp.Interpreter.Interop.Converters;

namespace MoonSharp.Interpreter.Interop.StandardDescriptors.HardwiredDescriptors
{
    public abstract class HardwiredMemberDescriptor : IMemberDescriptor
    {
        protected HardwiredMemberDescriptor(Type memberType, string name, bool isStatic, MemberDescriptorAccess access)
        {
            IsStatic = isStatic;
            Name = name;
            MemberAccess = access;
            MemberType = memberType;
        }

        public Type MemberType { get; }

        public bool IsStatic { get; }

        public string Name { get; }

        public MemberDescriptorAccess MemberAccess { get; }


        public DynValue GetValue(Script script, object obj)
        {
            this.CheckAccess(MemberDescriptorAccess.CanRead, obj);
            object result = GetValueImpl(script, obj);
            return ClrToScriptConversions.ObjectToDynValue(script, result);
        }

        public void SetValue(Script script, object obj, DynValue value)
        {
            this.CheckAccess(MemberDescriptorAccess.CanWrite, obj);
            object v = ScriptToClrConversions.DynValueToObjectOfType(value, MemberType, null, false);
            SetValueImpl(script, obj, v);
        }


        protected virtual object GetValueImpl(Script script, object obj)
        {
            throw new InvalidOperationException("GetValue on write-only hardwired descriptor " + Name);
        }

        protected virtual void SetValueImpl(Script script, object obj, object value)
        {
            throw new InvalidOperationException("SetValue on read-only hardwired descriptor " + Name);
        }
    }
}