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
    internal class WhileStatement : Statement
    {
        private readonly Statement m_Block;
        private readonly Expression m_Condition;
        private readonly SourceRef m_End;
        private readonly RuntimeScopeBlock m_StackFrame;
        private readonly SourceRef m_Start;

        public WhileStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            Token whileTk = CheckTokenType(lcontext, TokenType.While);

            m_Condition = Expression.Expr(lcontext);

            m_Start = whileTk.GetSourceRefUpTo(lcontext.Lexer.Current);

            //m_Start = BuildSourceRef(context.Start, exp.Stop);
            //m_End = BuildSourceRef(context.Stop, context.END());

            lcontext.Scope.PushBlock();
            CheckTokenType(lcontext, TokenType.Do);
            m_Block = new CompositeStatement(lcontext);
            m_End = CheckTokenType(lcontext, TokenType.End).GetSourceRef();
            m_StackFrame = lcontext.Scope.PopBlock();

            lcontext.Source.Refs.Add(m_Start);
            lcontext.Source.Refs.Add(m_End);
        }


        public override void Compile(ByteCode bc)
        {
            Loop L = new() {Scope = m_StackFrame};


            bc.LoopTracker.Loops.Push(L);

            bc.PushSourceRef(m_Start);

            var start = bc.GetJumpPointForNextInstruction();

            m_Condition.Compile(bc);
            var jumpend = bc.Emit_Jump(OpCode.Jf, -1);

            bc.Emit_Enter(m_StackFrame);

            m_Block.Compile(bc);

            bc.PopSourceRef();
            bc.Emit_Debug("..end");
            bc.PushSourceRef(m_End);

            bc.Emit_Leave(m_StackFrame);
            bc.Emit_Jump(OpCode.Jump, start);

            bc.LoopTracker.Loops.Pop();

            var exitpoint = bc.GetJumpPointForNextInstruction();

            foreach (Instruction i in L.BreakJumps)
                i.NumVal = exitpoint;

            jumpend.NumVal = exitpoint;

            bc.PopSourceRef();
        }
    }
}