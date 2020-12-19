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
    internal class GotoStatement : Statement
    {
        private Instruction m_Jump;
        private int m_LabelAddress = -1;

        public GotoStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            GotoToken = CheckTokenType(lcontext, TokenType.Goto);
            Token name = CheckTokenType(lcontext, TokenType.Name);

            SourceRef = GotoToken.GetSourceRef(name);

            Label = name.Text;

            lcontext.Scope.RegisterGoto(this);
        }

        internal SourceRef SourceRef { get; }
        internal Token GotoToken { get; }
        public string Label { get; }

        internal int DefinedVarsCount { get; private set; }
        internal string LastDefinedVarName { get; private set; }

        public override void Compile(ByteCode bc)
        {
            m_Jump = bc.Emit_Jump(OpCode.Jump, m_LabelAddress);
        }

        internal void SetDefinedVars(int definedVarsCount, string lastDefinedVarsName)
        {
            DefinedVarsCount = definedVarsCount;
            LastDefinedVarName = lastDefinedVarsName;
        }


        internal void SetAddress(int labelAddress)
        {
            m_LabelAddress = labelAddress;

            if (m_Jump != null)
                m_Jump.NumVal = labelAddress;
        }
    }
}