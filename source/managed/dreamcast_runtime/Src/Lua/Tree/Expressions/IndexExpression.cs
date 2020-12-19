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
    internal class IndexExpression : Expression, IVariable
    {
        private readonly Expression m_BaseExp;
        private readonly Expression m_IndexExp;
        private readonly string m_Name;


        public IndexExpression(Expression baseExp, Expression indexExp, ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            m_BaseExp = baseExp;
            m_IndexExp = indexExp;
        }

        public IndexExpression(Expression baseExp, string name, ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            m_BaseExp = baseExp;
            m_Name = name;
        }

        public void CompileAssignment(ByteCode bc, int stackofs, int tupleidx)
        {
            m_BaseExp.Compile(bc);

            if (m_Name != null)
            {
                bc.Emit_IndexSet(stackofs, tupleidx, DynValue.NewString(m_Name), true);
            }
            else if (m_IndexExp is LiteralExpression)
            {
                LiteralExpression lit = (LiteralExpression) m_IndexExp;
                bc.Emit_IndexSet(stackofs, tupleidx, lit.Value);
            }
            else
            {
                m_IndexExp.Compile(bc);
                bc.Emit_IndexSet(stackofs, tupleidx, isExpList: m_IndexExp is ExprListExpression);
            }
        }


        public override void Compile(ByteCode bc)
        {
            m_BaseExp.Compile(bc);

            if (m_Name != null)
            {
                bc.Emit_Index(DynValue.NewString(m_Name), true);
            }
            else if (m_IndexExp is LiteralExpression)
            {
                LiteralExpression lit = (LiteralExpression) m_IndexExp;
                bc.Emit_Index(lit.Value);
            }
            else
            {
                m_IndexExp.Compile(bc);
                bc.Emit_Index(isExpList: m_IndexExp is ExprListExpression);
            }
        }

        public override DynValue Eval(ScriptExecutionContext context)
        {
            DynValue b = m_BaseExp.Eval(context).ToScalar();
            DynValue i = m_IndexExp != null ? m_IndexExp.Eval(context).ToScalar() : DynValue.NewString(m_Name);

            if (b.Type != DataType.Table) throw new DynamicExpressionException("Attempt to index non-table.");
            if (i.IsNilOrNan()) throw new DynamicExpressionException("Attempt to index with nil or nan key.");
            return b.Table.Get(i) ?? DynValue.Nil;
        }
    }
}