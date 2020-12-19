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

namespace Dreamcast.Lua.Interpreter.Interop.StandardDescriptors
{
    internal class EventFacade : IUserDataType
    {
        private readonly Func<object, ScriptExecutionContext, CallbackArguments, DynValue> m_AddCallback;
        private readonly object m_Object;
        private readonly Func<object, ScriptExecutionContext, CallbackArguments, DynValue> m_RemoveCallback;

        public EventFacade(EventMemberDescriptor parent, object obj)
        {
            m_Object = obj;
            m_AddCallback = parent.AddCallback;
            m_RemoveCallback = parent.RemoveCallback;
        }

        public EventFacade(Func<object, ScriptExecutionContext, CallbackArguments, DynValue> addCallback, Func<object, ScriptExecutionContext, CallbackArguments, DynValue> removeCallback, object obj)
        {
            m_Object = obj;
            m_AddCallback = addCallback;
            m_RemoveCallback = removeCallback;
        }

        public DynValue Index(Script script, DynValue index, bool isDirectIndexing)
        {
            if (index.Type == DataType.String)
            {
                if (index.String == "add")
                    return DynValue.NewCallback((c, a) => m_AddCallback(m_Object, c, a));
                if (index.String == "remove")
                    return DynValue.NewCallback((c, a) => m_RemoveCallback(m_Object, c, a));
            }

            throw new ScriptRuntimeException("Events only support add and remove methods");
        }

        public bool SetIndex(Script script, DynValue index, DynValue value, bool isDirectIndexing)
        {
            throw new ScriptRuntimeException("Events do not have settable fields");
        }

        public DynValue MetaIndex(Script script, string metaname)
        {
            return null;
        }
    }
}