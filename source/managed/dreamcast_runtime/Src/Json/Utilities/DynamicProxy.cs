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

#if HAVE_DYNAMIC
using System.Collections.Generic;
using System.Dynamic;

namespace Dreamcast.Json.Utilities
{
    internal class DynamicProxy<T>
    {
        public virtual IEnumerable<string> GetDynamicMemberNames(T instance)
        {
            return CollectionUtils.ArrayEmpty<string>();
        }

        public virtual bool TryBinaryOperation(T instance, BinaryOperationBinder binder, object arg, out object? result)
        {
            result = null;
            return false;
        }

        public virtual bool TryConvert(T instance, ConvertBinder binder, out object? result)
        {
            result = null;
            return false;
        }

        public virtual bool TryCreateInstance(T instance, CreateInstanceBinder binder, object[] args, out object? result)
        {
            result = null;
            return false;
        }

        public virtual bool TryDeleteIndex(T instance, DeleteIndexBinder binder, object[] indexes)
        {
            return false;
        }

        public virtual bool TryDeleteMember(T instance, DeleteMemberBinder binder)
        {
            return false;
        }

        public virtual bool TryGetIndex(T instance, GetIndexBinder binder, object[] indexes, out object? result)
        {
            result = null;
            return false;
        }

        public virtual bool TryGetMember(T instance, GetMemberBinder binder, out object? result)
        {
            result = null;
            return false;
        }

        public virtual bool TryInvoke(T instance, InvokeBinder binder, object[] args, out object? result)
        {
            result = null;
            return false;
        }

        public virtual bool TryInvokeMember(T instance, InvokeMemberBinder binder, object[] args, out object? result)
        {
            result = null;
            return false;
        }

        public virtual bool TrySetIndex(T instance, SetIndexBinder binder, object[] indexes, object value)
        {
            return false;
        }

        public virtual bool TrySetMember(T instance, SetMemberBinder binder, object value)
        {
            return false;
        }

        public virtual bool TryUnaryOperation(T instance, UnaryOperationBinder binder, out object? result)
        {
            result = null;
            return false;
        }
    }
}

#endif