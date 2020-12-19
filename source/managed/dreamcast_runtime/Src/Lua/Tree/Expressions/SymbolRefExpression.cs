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

using MoonSharp.Interpreter.Execution;
using MoonSharp.Interpreter.Execution.VM;

namespace MoonSharp.Interpreter.Tree.Expressions
{
    internal class SymbolRefExpression : Expression, IVariable
    {
        private readonly SymbolRef m_Ref;
        private readonly string m_VarName;

        public SymbolRefExpression(Token T, ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            m_VarName = T.Text;

            if (T.Type == TokenType.VarArgs)
            {
                m_Ref = lcontext.Scope.Find(WellKnownSymbols.VARARGS);

                if (!lcontext.Scope.CurrentFunctionHasVarArgs())
                    throw new SyntaxErrorException(T, "cannot use '...' outside a vararg function");

                if (lcontext.IsDynamicExpression)
                    throw new DynamicExpressionException("cannot use '...' in a dynamic expression.");
            }
            else
            {
                if (!lcontext.IsDynamicExpression)
                    m_Ref = lcontext.Scope.Find(m_VarName);
            }

            lcontext.Lexer.Next();
        }

        public SymbolRefExpression(ScriptLoadingContext lcontext, SymbolRef refr)
            : base(lcontext)
        {
            m_Ref = refr;

            if (lcontext.IsDynamicExpression) throw new DynamicExpressionException("Unsupported symbol reference expression detected.");
        }


        public void CompileAssignment(ByteCode bc, int stackofs, int tupleidx)
        {
            bc.Emit_Store(m_Ref, stackofs, tupleidx);
        }

        public override void Compile(ByteCode bc)
        {
            bc.Emit_Load(m_Ref);
        }

        public override DynValue Eval(ScriptExecutionContext context)
        {
            return context.EvaluateSymbolByName(m_VarName);
        }

        public override SymbolRef FindDynamic(ScriptExecutionContext context)
        {
            return context.FindSymbolByName(m_VarName);
        }
    }
}