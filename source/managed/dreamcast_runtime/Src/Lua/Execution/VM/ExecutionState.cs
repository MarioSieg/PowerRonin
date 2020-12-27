using Dreamcast.Lua.Interpreter.DataStructs;

namespace Dreamcast.Lua.Interpreter.Execution.VM
{
    internal sealed class ExecutionState
    {
        public FastStack<CallStackItem> ExecutionStack = new(131072);
        public int InstructionPtr = 0;
        public CoroutineState State = CoroutineState.NotStarted;
        public FastStack<DynValue> ValueStack = new(131072);
    }
}