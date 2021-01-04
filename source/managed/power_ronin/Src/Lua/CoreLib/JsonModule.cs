using PowerRonin.Lua.Interpreter.Serialization.Json;

namespace PowerRonin.Lua.Interpreter.CoreLib
{
    [LuaModule(Namespace = "json")]
    public class JsonModule
    {
        [LuaModuleMethod]
        public static DynValue parse(ScriptExecutionContext executionContext, CallbackArguments args)
        {
            try
            {
                DynValue vs = args.AsType(0, "parse", DataType.String);
                Table t = JsonTableConverter.JsonToTable(vs.String, executionContext.GetScript());
                return DynValue.NewTable(t);
            }
            catch (SyntaxErrorException ex)
            {
                throw new ScriptRuntimeException(ex);
            }
        }

        [LuaModuleMethod]
        public static DynValue serialize(ScriptExecutionContext executionContext, CallbackArguments args)
        {
            try
            {
                DynValue vt = args.AsType(0, "serialize", DataType.Table);
                string s = vt.Table.TableToJson();
                return DynValue.NewString(s);
            }
            catch (SyntaxErrorException ex)
            {
                throw new ScriptRuntimeException(ex);
            }
        }

        [LuaModuleMethod]
        public static DynValue isnull(ScriptExecutionContext executionContext, CallbackArguments args)
        {
            DynValue vs = args[0];
            return DynValue.NewBoolean(JsonNull.IsJsonNull(vs) || vs.IsNil());
        }

        [LuaModuleMethod]
        public static DynValue @null(ScriptExecutionContext executionContext, CallbackArguments args)
        {
            return JsonNull.Create();
        }
    }
}