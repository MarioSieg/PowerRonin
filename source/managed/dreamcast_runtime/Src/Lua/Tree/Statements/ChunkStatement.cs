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

using Dreamcast.Lua.Interpreter.Execution;
using Dreamcast.Lua.Interpreter.Execution.VM;

namespace Dreamcast.Lua.Interpreter.Tree.Statements
{
    internal class ChunkStatement : Statement, IClosureBuilder
    {
        private readonly Statement m_Block;
        private readonly SymbolRef m_Env;
        private readonly RuntimeScopeFrame m_StackFrame;
        private readonly SymbolRef m_VarArgs;

        public ChunkStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            lcontext.Scope.PushFunction(this, true);
            m_Env = lcontext.Scope.DefineLocal(WellKnownSymbols.ENV);
            m_VarArgs = lcontext.Scope.DefineLocal(WellKnownSymbols.VARARGS);

            m_Block = new CompositeStatement(lcontext);

            if (lcontext.Lexer.Current.Type != TokenType.Eof)
                throw new SyntaxErrorException(lcontext.Lexer.Current, "<eof> expected near '{0}'", lcontext.Lexer.Current.Text);

            m_StackFrame = lcontext.Scope.PopFunction();
        }

        public SymbolRef CreateUpvalue(BuildTimeScope scope, SymbolRef symbol)
        {
            return null;
        }


        public override void Compile(ByteCode bc)
        {
            Instruction meta = bc.Emit_Meta("<chunk-root>", OpCodeMetadataType.ChunkEntrypoint);
            var metaip = bc.GetJumpPointForLastInstruction();

            bc.Emit_BeginFn(m_StackFrame);
            bc.Emit_Args(m_VarArgs);

            bc.Emit_Load(SymbolRef.Upvalue(WellKnownSymbols.ENV, 0));
            bc.Emit_Store(m_Env, 0, 0);
            bc.Emit_Pop();

            m_Block.Compile(bc);
            bc.Emit_Ret(0);

            meta.NumVal = bc.GetJumpPointForLastInstruction() - metaip;
        }
    }
}