using System.Collections.Generic;
using PowerRonin.Lua.Interpreter.Execution;
using PowerRonin.Lua.Interpreter.Execution.VM;

namespace PowerRonin.Lua.Interpreter.Tree
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