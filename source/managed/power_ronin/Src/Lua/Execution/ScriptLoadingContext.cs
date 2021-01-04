using PowerRonin.Lua.Interpreter.Debugging;
using PowerRonin.Lua.Interpreter.Tree;

namespace PowerRonin.Lua.Interpreter.Execution
{
    internal class ScriptLoadingContext
    {
        public ScriptLoadingContext(Script s)
        {
            Script = s;
        }

        public Script Script { get; }
        public BuildTimeScope Scope { get; set; }
        public SourceCode Source { get; set; }
        public bool Anonymous { get; set; }
        public bool IsDynamicExpression { get; set; }
        public Lexer Lexer { get; set; }
    }
}