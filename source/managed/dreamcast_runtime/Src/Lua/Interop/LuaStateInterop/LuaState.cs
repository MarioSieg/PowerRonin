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

#pragma warning disable 1591

using System.Collections.Generic;

namespace Dreamcast.Lua.Interpreter.Interop.LuaStateInterop
{
    /// <summary>
    /// </summary>
    public class LuaState
    {
        private readonly List<DynValue> m_Stack;

        internal LuaState(ScriptExecutionContext executionContext, CallbackArguments args, string functionName)
        {
            ExecutionContext = executionContext;
            m_Stack = new List<DynValue>(16);

            for (var i = 0; i < args.Count; i++)
                m_Stack.Add(args[i]);

            FunctionName = functionName;
        }

        public ScriptExecutionContext ExecutionContext { get; }
        public string FunctionName { get; }

        public int Count => m_Stack.Count;

        public DynValue Top(int pos = 0)
        {
            return m_Stack[m_Stack.Count - 1 - pos];
        }

        public DynValue At(int pos)
        {
            if (pos < 0)
                pos = m_Stack.Count + pos + 1;

            if (pos > m_Stack.Count)
                return DynValue.Void;

            return m_Stack[pos - 1];
        }

        public void Push(DynValue v)
        {
            m_Stack.Add(v);
        }

        public DynValue Pop()
        {
            var v = Top();
            m_Stack.RemoveAt(m_Stack.Count - 1);
            return v;
        }

        public DynValue[] GetTopArray(int num)
        {
            DynValue[] rets = new DynValue[num];

            for (var i = 0; i < num; i++)
                rets[num - i - 1] = Top(i);

            return rets;
        }


        public DynValue GetReturnValue(int retvals)
        {
            if (retvals == 0) return DynValue.Nil;

            if (retvals == 1)
            {
                return Top();
            }

            DynValue[] rets = GetTopArray(retvals);
            return DynValue.NewTupleNested(rets);
        }


        public void Discard(int nargs)
        {
            for (var i = 0; i < nargs; i++)
                m_Stack.RemoveAt(m_Stack.Count - 1);
        }
    }
}