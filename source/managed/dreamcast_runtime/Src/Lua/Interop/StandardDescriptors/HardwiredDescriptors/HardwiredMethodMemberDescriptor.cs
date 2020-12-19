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

using System.Collections.Generic;
using Dreamcast.Lua.Interpreter.Interop.BasicDescriptors;

namespace Dreamcast.Lua.Interpreter.Interop.StandardDescriptors.HardwiredDescriptors
{
    public abstract class HardwiredMethodMemberDescriptor : FunctionMemberDescriptorBase
    {
        public override DynValue Execute(Script script, object obj, ScriptExecutionContext context, CallbackArguments args)
        {
            this.CheckAccess(MemberDescriptorAccess.CanExecute, obj);

            List<int> outParams = null;
            object[] pars = base.BuildArgumentList(script, obj, context, args, out outParams);
            object retv = Invoke(script, obj, pars, CalcArgsCount(pars));

            return DynValue.FromObject(script, retv);
        }

        private int CalcArgsCount(object[] pars)
        {
            var count = pars.Length;

            for (var i = 0; i < pars.Length; i++)
                if (Parameters[i].HasDefaultValue && pars[i] is DefaultValue)
                    count -= 1;

            return count;
        }

        protected abstract object Invoke(Script script, object obj, object[] pars, int argscount);
    }
}