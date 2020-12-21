#pragma warning disable 1591


namespace Dreamcast.Lua.Interpreter.CoreLib
{
    /// <summary>
    ///     Class implementing dynamic expression evaluations at runtime (a Dreamcast.Lua addition).
    /// </summary>
    [LuaModule(Namespace = "dynamic")]
    public class DynamicModule
    {
        public static void LuaInit(Table globalTable, Table stringTable)
        {
            UserData.RegisterType<DynamicExprWrapper>(InteropAccessMode.HideMembers);
        }

        [LuaModuleMethod]
        public static DynValue eval(ScriptExecutionContext executionContext, CallbackArguments args)
        {
            try
            {
                if (args[0].Type == DataType.UserData)
                {
                    UserData ud = args[0].UserData;
                    if (ud.Object is DynamicExprWrapper)
                        return ((DynamicExprWrapper) ud.Object).Expr.Evaluate(executionContext);
                    throw ScriptRuntimeException.BadArgument(0, "dynamic.eval",
                        "A userdata was passed, but was not a previously prepared expression.");
                }

                DynValue vs = args.AsType(0, "dynamic.eval", DataType.String);
                DynamicExpression expr = executionContext.GetScript().CreateDynamicExpression(vs.String);
                return expr.Evaluate(executionContext);
            }
            catch (SyntaxErrorException ex)
            {
                throw new ScriptRuntimeException(ex);
            }
        }

        [LuaModuleMethod]
        public static DynValue prepare(ScriptExecutionContext executionContext, CallbackArguments args)
        {
            try
            {
                DynValue vs = args.AsType(0, "dynamic.prepare", DataType.String);
                DynamicExpression expr = executionContext.GetScript().CreateDynamicExpression(vs.String);
                return UserData.Create(new DynamicExprWrapper {Expr = expr});
            }
            catch (SyntaxErrorException ex)
            {
                throw new ScriptRuntimeException(ex);
            }
        }

        private class DynamicExprWrapper
        {
            public DynamicExpression Expr;
        }
    }
}