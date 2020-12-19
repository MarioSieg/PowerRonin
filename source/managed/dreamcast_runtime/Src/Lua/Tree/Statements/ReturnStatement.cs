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

using Dreamcast.Lua.Interpreter.Debugging;
using Dreamcast.Lua.Interpreter.Execution;
using Dreamcast.Lua.Interpreter.Execution.VM;
using Dreamcast.Lua.Interpreter.Tree.Expressions;

namespace Dreamcast.Lua.Interpreter.Tree.Statements
{
    internal class ReturnStatement : Statement
    {
        private readonly Expression m_Expression;
        private readonly SourceRef m_Ref;

        public ReturnStatement(ScriptLoadingContext lcontext, Expression e, SourceRef sref)
            : base(lcontext)
        {
            m_Expression = e;
            m_Ref = sref;
            lcontext.Source.Refs.Add(sref);
        }


        public ReturnStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            Token ret = lcontext.Lexer.Current;

            lcontext.Lexer.Next();

            Token cur = lcontext.Lexer.Current;

            if (cur.IsEndOfBlock() || cur.Type == TokenType.SemiColon)
            {
                m_Expression = null;
                m_Ref = ret.GetSourceRef();
            }
            else
            {
                m_Expression = new ExprListExpression(Expression.ExprList(lcontext), lcontext);
                m_Ref = ret.GetSourceRefUpTo(lcontext.Lexer.Current);
            }

            lcontext.Source.Refs.Add(m_Ref);
        }


        public override void Compile(ByteCode bc)
        {
            using (bc.EnterSource(m_Ref))
            {
                if (m_Expression != null)
                {
                    m_Expression.Compile(bc);
                    bc.Emit_Ret(1);
                }
                else
                {
                    bc.Emit_Ret(0);
                }
            }
        }
    }
}