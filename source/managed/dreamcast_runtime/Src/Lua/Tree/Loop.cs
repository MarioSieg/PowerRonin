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

namespace Dreamcast.Lua.Interpreter.Tree
{
    internal class Loop : ILoop
    {
        public List<Instruction> BreakJumps = new();
        public RuntimeScopeBlock Scope;

        public void CompileBreak(ByteCode bc)
        {
            bc.Emit_Exit(Scope);
            BreakJumps.Add(bc.Emit_Jump(OpCode.Jump, -1));
        }

        public bool IsBoundary()
        {
            return false;
        }
    }

    internal class LoopBoundary : ILoop
    {
        public void CompileBreak(ByteCode bc)
        {
            throw new InternalErrorException("CompileBreak called on LoopBoundary");
        }

        public bool IsBoundary()
        {
            return true;
        }
    }
}