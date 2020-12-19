// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 2013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#pragma warning disable 1591


namespace Dreamcast.Lua.Interpreter.CoreLib
{
    /// <summary>
    ///     Class implementing dynamic expression evaluations at runtime (a Dreamcast.Lua addition).
    /// </summary>
    [Dreamcast.LuaModule(Namespace = "dynamic")]
    public class DynamicModule
    {
        public static void Dreamcast.LuaInit(Table globalTable, Table stringTable)
        {
            UserData.RegisterType<DynamicExprWrapper>(InteropAccessMode.HideMembers);
        }

        [Dreamcast.LuaModuleMethod]
        public static DynValue eval(ScriptExecutionContext executionContext, CallbackArguments args)
        {
            try
            {
                if (args[0].Type == DataType.UserData)
                {
                    UserData ud = args[0].UserData;
                    if (ud.Object is DynamicExprWrapper)
                        return ((DynamicExprWrapper) ud.Object).Expr.Evaluate(executionContext);
                    throw ScriptRuntimeException.BadArgument(0, "dynamic.eval", "A userdata was passed, but was not a previously prepared expression.");
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

        [Dreamcast.LuaModuleMethod]
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