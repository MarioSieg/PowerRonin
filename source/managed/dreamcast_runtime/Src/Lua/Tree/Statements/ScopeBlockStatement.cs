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

namespace Dreamcast.Lua.Interpreter.Tree.Statements
{
    internal class ScopeBlockStatement : Statement
    {
        private readonly Statement m_Block;
        private readonly SourceRef m_Do;
        private readonly SourceRef m_End;
        private readonly RuntimeScopeBlock m_StackFrame;

        public ScopeBlockStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            lcontext.Scope.PushBlock();

            m_Do = CheckTokenType(lcontext, TokenType.Do).GetSourceRef();

            m_Block = new CompositeStatement(lcontext);

            m_End = CheckTokenType(lcontext, TokenType.End).GetSourceRef();

            m_StackFrame = lcontext.Scope.PopBlock();
            lcontext.Source.Refs.Add(m_Do);
            lcontext.Source.Refs.Add(m_End);
        }


        public override void Compile(ByteCode bc)
        {
            using (bc.EnterSource(m_Do))
            {
                bc.Emit_Enter(m_StackFrame);
            }

            m_Block.Compile(bc);

            using (bc.EnterSource(m_End))
            {
                bc.Emit_Leave(m_StackFrame);
            }
        }
    }
}