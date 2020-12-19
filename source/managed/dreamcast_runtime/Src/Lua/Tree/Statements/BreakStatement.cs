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

using MoonSharp.Interpreter.Debugging;
using MoonSharp.Interpreter.Execution;
using MoonSharp.Interpreter.Execution.VM;

namespace MoonSharp.Interpreter.Tree.Statements
{
    internal class BreakStatement : Statement
    {
        private readonly SourceRef m_Ref;

        public BreakStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            m_Ref = CheckTokenType(lcontext, TokenType.Break).GetSourceRef();
            lcontext.Source.Refs.Add(m_Ref);
        }


        public override void Compile(ByteCode bc)
        {
            using (bc.EnterSource(m_Ref))
            {
                if (bc.LoopTracker.Loops.Count == 0)
                    throw new SyntaxErrorException(Script, m_Ref, "<break> at line {0} not inside a loop", m_Ref.FromLine);

                ILoop loop = bc.LoopTracker.Loops.Peek();

                if (loop.IsBoundary())
                    throw new SyntaxErrorException(Script, m_Ref, "<break> at line {0} not inside a loop", m_Ref.FromLine);

                loop.CompileBreak(bc);
            }
        }
    }
}