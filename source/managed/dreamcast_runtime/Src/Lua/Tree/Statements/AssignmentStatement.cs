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
using System.Collections.Generic;
using MoonSharp.Interpreter.Debugging;
using MoonSharp.Interpreter.Execution;
using MoonSharp.Interpreter.Execution.VM;
using MoonSharp.Interpreter.Tree.Expressions;

namespace MoonSharp.Interpreter.Tree.Statements
{
    internal class AssignmentStatement : Statement
    {
        private readonly List<IVariable> m_LValues = new();
        private readonly SourceRef m_Ref;
        private readonly List<Expression> m_RValues;


        public AssignmentStatement(ScriptLoadingContext lcontext, Token startToken)
            : base(lcontext)
        {
            List<string> names = new();

            Token first = startToken;

            while (true)
            {
                Token name = CheckTokenType(lcontext, TokenType.Name);
                names.Add(name.Text);

                if (lcontext.Lexer.Current.Type != TokenType.Comma)
                    break;

                lcontext.Lexer.Next();
            }

            if (lcontext.Lexer.Current.Type == TokenType.Op_Assignment)
            {
                CheckTokenType(lcontext, TokenType.Op_Assignment);
                m_RValues = Expression.ExprList(lcontext);
            }
            else
            {
                m_RValues = new List<Expression>();
            }

            foreach (string name in names)
            {
                var localVar = lcontext.Scope.TryDefineLocal(name);
                var symbol = new SymbolRefExpression(lcontext, localVar);
                m_LValues.Add(symbol);
            }

            Token last = lcontext.Lexer.Current;
            m_Ref = first.GetSourceRefUpTo(last);
            lcontext.Source.Refs.Add(m_Ref);
        }


        public AssignmentStatement(ScriptLoadingContext lcontext, Expression firstExpression, Token first)
            : base(lcontext)
        {
            m_LValues.Add(CheckVar(lcontext, firstExpression));

            while (lcontext.Lexer.Current.Type == TokenType.Comma)
            {
                lcontext.Lexer.Next();
                Expression e = Expression.PrimaryExp(lcontext);
                m_LValues.Add(CheckVar(lcontext, e));
            }

            CheckTokenType(lcontext, TokenType.Op_Assignment);

            m_RValues = Expression.ExprList(lcontext);

            Token last = lcontext.Lexer.Current;
            m_Ref = first.GetSourceRefUpTo(last);
            lcontext.Source.Refs.Add(m_Ref);
        }

        private IVariable CheckVar(ScriptLoadingContext lcontext, Expression firstExpression)
        {
            IVariable v = firstExpression as IVariable;

            if (v == null)
                throw new SyntaxErrorException(lcontext.Lexer.Current, "unexpected symbol near '{0}' - not a l-value", lcontext.Lexer.Current);

            return v;
        }


        public override void Compile(ByteCode bc)
        {
            using (bc.EnterSource(m_Ref))
            {
                foreach (var exp in m_RValues) exp.Compile(bc);

                for (var i = 0; i < m_LValues.Count; i++)
                    m_LValues[i].CompileAssignment(bc,
                        Math.Max(m_RValues.Count - 1 - i, 0), // index of r-value
                        i - Math.Min(i, m_RValues.Count - 1)); // index in last tuple

                bc.Emit_Pop(m_RValues.Count);
            }
        }
    }
}