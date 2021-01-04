using PowerRonin.Lua.Interpreter.Execution;
using PowerRonin.Lua.Interpreter.Execution.VM;

namespace PowerRonin.Lua.Interpreter.Tree.Statements
{
    internal class EmptyStatement : Statement
    {
        public EmptyStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
        }


        public override void Compile(ByteCode bc)
        {
        }
    }
}