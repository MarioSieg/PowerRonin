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
using Dreamcast.Lua.Interpreter.Interop.BasicDescriptors;
using Dreamcast.Lua.Interpreter.Interop.Converters;

namespace Dreamcast.Lua.Interpreter.Interop
{
    /// <summary>
    ///     Member descriptor for indexer of array types
    /// </summary>
    public class ArrayMemberDescriptor : ObjectCallbackMemberDescriptor, IWireableDescriptor
    {
        private readonly bool m_IsSetter;

        /// <summary>
        ///     Initializes a new instance of the <see cref="ArrayMemberDescriptor" /> class.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="isSetter">if set to <c>true</c> is a setter indexer.</param>
        /// <param name="indexerParams">The indexer parameters.</param>
        public ArrayMemberDescriptor(string name, bool isSetter, ParameterDescriptor[] indexerParams)
            : base(
                name,
                isSetter ? ArrayIndexerSet : (Func<object, ScriptExecutionContext, CallbackArguments, object>) ArrayIndexerGet,
                indexerParams)
        {
            m_IsSetter = isSetter;
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="ArrayMemberDescriptor" /> class.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="isSetter">if set to <c>true</c> [is setter].</param>
        public ArrayMemberDescriptor(string name, bool isSetter)
            : base(
                name,
                isSetter ? ArrayIndexerSet : (Func<object, ScriptExecutionContext, CallbackArguments, object>) ArrayIndexerGet)
        {
            m_IsSetter = isSetter;
        }

        /// <summary>
        ///     Prepares the descriptor for hard-wiring.
        ///     The descriptor fills the passed table with all the needed data for hardwire generators to generate the appropriate
        ///     code.
        /// </summary>
        /// <param name="t">The table to be filled</param>
        public void PrepareForWiring(Table t)
        {
            t.Set("class", DynValue.NewString(GetType().FullName));
            t.Set("name", DynValue.NewString(Name));
            t.Set("setter", DynValue.NewBoolean(m_IsSetter));

            if (Parameters != null)
            {
                var pars = DynValue.NewPrimeTable();

                t.Set("params", pars);

                var i = 0;

                foreach (var p in Parameters)
                {
                    DynValue pt = DynValue.NewPrimeTable();
                    pars.Table.Set(++i, pt);
                    p.PrepareForWiring(pt.Table);
                }
            }
        }

        private static int[] BuildArrayIndices(CallbackArguments args, int count)
        {
            int[] indices = new int[count];

            for (var i = 0; i < count; i++)
                indices[i] = args.AsInt(i, "userdata_array_indexer");

            return indices;
        }

        private static object ArrayIndexerSet(object arrayObj, ScriptExecutionContext ctx, CallbackArguments args)
        {
            Array array = (Array) arrayObj;
            int[] indices = BuildArrayIndices(args, args.Count - 1);
            DynValue value = args[args.Count - 1];

            Type elemType = array.GetType().GetElementType();

            object objValue = ScriptToClrConversions.DynValueToObjectOfType(value, elemType, null, false);

            array.SetValue(objValue, indices);

            return DynValue.Void;
        }


        private static object ArrayIndexerGet(object arrayObj, ScriptExecutionContext ctx, CallbackArguments args)
        {
            Array array = (Array) arrayObj;
            int[] indices = BuildArrayIndices(args, args.Count);

            return array.GetValue(indices);
        }
    }
}