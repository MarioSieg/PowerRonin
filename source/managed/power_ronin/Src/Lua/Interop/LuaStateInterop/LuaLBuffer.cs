#pragma warning disable 1591

using System.Text;

namespace PowerRonin.Lua.Interpreter.Interop.LuaStateInterop
{
    public class LuaLBuffer
    {
        public LuaLBuffer(LuaState l)
        {
            StringBuilder = new StringBuilder();
            LuaState = l;
        }

        public StringBuilder StringBuilder { get; }
        public LuaState LuaState { get; }
    }
}