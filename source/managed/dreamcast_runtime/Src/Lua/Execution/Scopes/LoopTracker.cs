using Dreamcast.Lua.Interpreter.DataStructs;
using Dreamcast.Lua.Interpreter.Execution.VM;

namespace Dreamcast.Lua.Interpreter.Execution
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