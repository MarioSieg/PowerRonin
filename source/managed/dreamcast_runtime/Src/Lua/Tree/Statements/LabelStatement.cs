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
using Dreamcast.Lua.Interpreter.Debugging;
using Dreamcast.Lua.Interpreter.Execution;
using Dreamcast.Lua.Interpreter.Execution.VM;

namespace Dreamcast.Lua.Interpreter.Tree.Statements
{
    internal class LabelStatement : Statement
    {
        private readonly List<GotoStatement> m_Gotos = new();
        private RuntimeScopeBlock m_StackFrame;


        public LabelStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            CheckTokenType(lcontext, TokenType.DoubleColon);
            NameToken = CheckTokenType(lcontext, TokenType.Name);
            CheckTokenType(lcontext, TokenType.DoubleColon);

            SourceRef = NameToken.GetSourceRef();
            Label = NameToken.Text;

            lcontext.Scope.DefineLabel(this);
        }

        public string Label { get; }
        public int Address { get; private set; }
        public SourceRef SourceRef { get; }
        public Token NameToken { get; }

        internal int DefinedVarsCount { get; private set; }
        internal string LastDefinedVarName { get; private set; }

        internal void SetDefinedVars(int definedVarsCount, string lastDefinedVarsName)
        {
            DefinedVarsCount = definedVarsCount;
            LastDefinedVarName = lastDefinedVarsName;
        }

        internal void RegisterGoto(GotoStatement gotostat)
        {
            m_Gotos.Add(gotostat);
        }


        public override void Compile(ByteCode bc)
        {
            bc.Emit_Clean(m_StackFrame);

            Address = bc.GetJumpPointForLastInstruction();

            foreach (var gotostat in m_Gotos)
                gotostat.SetAddress(Address);
        }

        internal void SetScope(RuntimeScopeBlock runtimeScopeBlock)
        {
            m_StackFrame = runtimeScopeBlock;
        }
    }
}