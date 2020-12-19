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
using System.Collections;
using System.Reflection;
using Dreamcast.Lua.Interpreter.Compatibility;
using Dreamcast.Lua.Interpreter.Interop.Converters;

namespace Dreamcast.Lua.Interpreter.Serialization
{
    public static class ObjectValueConverter
    {
        public static DynValue SerializeObjectToDynValue(Script script, object o, DynValue valueForNulls = null)
        {
            if (o == null)
                return valueForNulls ?? DynValue.Nil;

            DynValue v = ClrToScriptConversions.TryObjectToTrivialDynValue(script, o);

            if (v != null)
                return v;

            if (o is Enum)
                return DynValue.NewNumber(NumericConversions.TypeToDouble(Enum.GetUnderlyingType(o.GetType()), o));

            Table t = new(script);

            IEnumerable ienum = o as IEnumerable;

            if (ienum != null)
            {
                foreach (object obj in ienum) t.Append(SerializeObjectToDynValue(script, obj, valueForNulls));
            }
            else
            {
                Type type = o.GetType();

                foreach (PropertyInfo pi in Framework.Do.GetProperties(type))
                {
                    var getter = Framework.Do.GetGetMethod(pi);
                    var isStatic = getter.IsStatic;
                    var obj = getter.Invoke(isStatic ? null : o, null); // convoluted workaround for --full-aot Mono execution

                    t.Set(pi.Name, SerializeObjectToDynValue(script, obj, valueForNulls));
                }
            }

            return DynValue.NewTable(t);
        }
    }
}