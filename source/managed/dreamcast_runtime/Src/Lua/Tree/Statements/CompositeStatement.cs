using System.Collections.Generic;
using Dreamcast.Lua.Interpreter.Execution;
using Dreamcast.Lua.Interpreter.Execution.VM;

namespace Dreamcast.Lua.Interpreter.Tree.Statements
{
    internal class CompositeStatement : Statement
    {
        private readonly List<Statement> m_Statements = new();

        public CompositeStatement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
            while (true)
            {
                Token t = lcontext.Lexer.Current;
                if (t.IsEndOfBlock()) break;

                bool forceLast;

                Statement s = CreateStatement(lcontext, out forceLast);
                m_Statements.Add(s);

                if (forceLast) break;
            }

            // eat away all superfluos ';'s
            while (lcontext.Lexer.Current.Type == TokenType.SemiColon)
                lcontext.Lexer.Next();
        }


        public override void Compile(ByteCode bc)
        {
            if (m_Statements != null)
                foreach (Statement s in m_Statements)
                    s.Compile(bc);
        }
    }
}