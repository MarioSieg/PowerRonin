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

namespace Dreamcast.Lua.Interpreter.Tree.Statements
{
    internal class CompositeStatement : Statement
    {
        private readonly List<Statement> m_Statements = new();

        public CompositeStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            while (true)
            {
                Token t = lcontext.Lexer.Current;
                if (t.IsEndOfBlock()) break;

                bool forceLast;

                Statement s = CreateStatement(lcontext, out forceLast);
                m_Statements.Add(s);

                if (forceLast) break;
            }

            // eat away all superfluos ';'s
            while (lcontext.Lexer.Current.Type == TokenType.SemiColon)
                lcontext.Lexer.Next();
        }


        public override void Compile(ByteCode bc)
        {
            if (m_Statements != null)
                foreach (Statement s in m_Statements)
                    s.Compile(bc);
        }
    }
}