using Dreamcast.Lua.Interpreter.Execution.VM;

namespace Dreamcast.Lua.Interpreter.Tree
{
    internal interface IVariable
    {
        void CompileAssignment(ByteCode bc, int stackofs, int tupleidx);
    }
}