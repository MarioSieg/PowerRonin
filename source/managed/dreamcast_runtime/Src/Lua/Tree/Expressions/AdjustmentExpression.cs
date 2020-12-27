using Dreamcast.Lua.Interpreter.Execution;
using Dreamcast.Lua.Interpreter.Execution.VM;

namespace Dreamcast.Lua.Interpreter.Tree.Expressions
{
    internal class AdjustmentExpression : Expression
    {
        private readonly Expression expression;

        public AdjustmentExpression(ScriptLoadingContext lcontext, Expression exp)
            : base(lcontext)
        {
            expression = exp;
        }

        public override void Compile(ByteCode bc)
        {
            expression.Compile(bc);
            bc.Emit_Scalar();
        }

        public override DynValue Eval(ScriptExecutionContext context)
        {
            return expression.Eval(context).ToScalar();
        }
    }
}