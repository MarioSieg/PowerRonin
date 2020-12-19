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
using Dreamcast.Lua.Interpreter.Execution;
using Dreamcast.Lua.Interpreter.Execution.VM;

namespace Dreamcast.Lua.Interpreter.Tree.Expressions
{
    internal class ExprListExpression : Expression
    {
        private readonly List<Expression> expressions;

        public ExprListExpression(List<Expression> exps, ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            expressions = exps;
        }


        public Expression[] GetExpressions()
        {
            return expressions.ToArray();
        }

        public override void Compile(ByteCode bc)
        {
            foreach (var exp in expressions)
                exp.Compile(bc);

            if (expressions.Count > 1)
                bc.Emit_MkTuple(expressions.Count);
        }

        public override DynValue Eval(ScriptExecutionContext context)
        {
            if (expressions.Count >= 1)
                return expressions[0].Eval(context);

            return DynValue.Void;
        }
    }
}