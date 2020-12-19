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
using MoonSharp.Interpreter.Tree.Expressions;

namespace MoonSharp.Interpreter.Tree.Statements
{
    internal class FunctionCallStatement : Statement
    {
        private readonly FunctionCallExpression m_FunctionCallExpression;

        public FunctionCallStatement(ScriptLoadingContext lcontext, FunctionCallExpression functionCallExpression)
            : base(lcontext)
        {
            m_FunctionCallExpression = functionCallExpression;
            lcontext.Source.Refs.Add(m_FunctionCallExpression.SourceRef);
        }


        public override void Compile(ByteCode bc)
        {
            using (bc.EnterSource(m_FunctionCallExpression.SourceRef))
            {
                m_FunctionCallExpression.Compile(bc);
                RemoveBreakpointStop(bc.Emit_Pop());
            }
        }

        private void RemoveBreakpointStop(Instruction instruction)
        {
            instruction.SourceCodeRef = null;
        }
    }
}