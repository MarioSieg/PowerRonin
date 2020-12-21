using Dreamcast.Lua.Interpreter.Execution;
using Dreamcast.Lua.Interpreter.Execution.VM;

namespace Dreamcast.Lua.Interpreter.Tree.Statements
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