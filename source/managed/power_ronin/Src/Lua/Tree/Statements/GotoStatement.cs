using PowerRonin.Lua.Interpreter.Debugging;
using PowerRonin.Lua.Interpreter.Execution;
using PowerRonin.Lua.Interpreter.Execution.VM;

namespace PowerRonin.Lua.Interpreter.Tree.Statements
{
    internal class GotoStatement : Statement
    {
        private Instruction m_Jump;
        private int m_LabelAddress = -1;

        public GotoStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            GotoToken = CheckTokenType(lcontext, TokenType.Goto);
            Token name = CheckTokenType(lcontext, TokenType.Name);

            SourceRef = GotoToken.GetSourceRef(name);

            Label = name.Text;

            lcontext.Scope.RegisterGoto(this);
        }

        internal SourceRef SourceRef { get; }
        internal Token GotoToken { get; }
        public string Label { get; }

        internal int DefinedVarsCount { get; private set; }
        internal string LastDefinedVarName { get; private set; }

        public override void Compile(ByteCode bc)
        {
            m_Jump = bc.Emit_Jump(OpCode.Jump, m_LabelAddress);
        }

        internal void SetDefinedVars(int definedVarsCount, string lastDefinedVarsName)
        {
            DefinedVarsCount = definedVarsCount;
            LastDefinedVarName = lastDefinedVarsName;
        }


        internal void SetAddress(int labelAddress)
        {
            m_LabelAddress = labelAddress;

            if (m_Jump != null)
                m_Jump.NumVal = labelAddress;
        }
    }
}