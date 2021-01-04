using PowerRonin.Lua.Interpreter.Execution.VM;

namespace PowerRonin.Lua.Interpreter.Tree
{
    internal interface IVariable
    {
        void CompileAssignment(ByteCode bc, int stackofs, int tupleidx);
    }
}