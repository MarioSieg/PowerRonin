using PowerRonin.Lua.Interpreter.DataStructs;
using PowerRonin.Lua.Interpreter.Execution.VM;

namespace PowerRonin.Lua.Interpreter.Execution
{
    internal interface ILoop
    {
        void CompileBreak(ByteCode bc);
        bool IsBoundary();
    }


    internal class LoopTracker
    {
        public FastStack<ILoop> Loops = new(16384);
    }
}