using PowerRonin.Lua.Interpreter;

namespace PowerRonin.Core
{
    /// <summary>
    ///     Contains helpers and methods to execute Lua scripts.
    /// </summary>
    public static class Lua
    {
        /// <summary>
        ///     Runs a lua script file.
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public static DynValue RunScript(string filePath)
        {
            return Script.RunFile(filePath);
        }

        /// <summary>
        ///     Runs a script as string.
        /// </summary>
        /// <param name="scriptText"></param>
        /// <returns></returns>
        public static DynValue RunString(string scriptText)
        {
            return Script.RunString(scriptText);
        }
    }
}