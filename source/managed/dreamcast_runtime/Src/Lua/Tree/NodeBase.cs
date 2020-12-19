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

using Dreamcast.Lua.Interpreter.Execution;
using Dreamcast.Lua.Interpreter.Execution.VM;

namespace Dreamcast.Lua.Interpreter.Tree
{
    internal abstract class NodeBase
    {
        public NodeBase(ScriptLoadingContext lcontext)
        {
            Script = lcontext.Script;
        }

        public Script Script { get; }
        protected ScriptLoadingContext LoadingContext { get; private set; }


        public abstract void Compile(ByteCode bc);


        protected static Token UnexpectedTokenType(Token t)
        {
            throw new SyntaxErrorException(t, "unexpected symbol near '{0}'", t.Text) {IsPrematureStreamTermination = t.Type == TokenType.Eof};
        }

        protected static Token CheckTokenType(ScriptLoadingContext lcontext, TokenType tokenType)
        {
            Token t = lcontext.Lexer.Current;
            if (t.Type != tokenType)
                return UnexpectedTokenType(t);

            lcontext.Lexer.Next();

            return t;
        }


        protected static Token CheckTokenType(ScriptLoadingContext lcontext, TokenType tokenType1, TokenType tokenType2)
        {
            Token t = lcontext.Lexer.Current;
            if (t.Type != tokenType1 && t.Type != tokenType2)
                return UnexpectedTokenType(t);

            lcontext.Lexer.Next();

            return t;
        }

        protected static Token CheckTokenType(ScriptLoadingContext lcontext, TokenType tokenType1, TokenType tokenType2, TokenType tokenType3)
        {
            Token t = lcontext.Lexer.Current;
            if (t.Type != tokenType1 && t.Type != tokenType2 && t.Type != tokenType3)
                return UnexpectedTokenType(t);

            lcontext.Lexer.Next();

            return t;
        }

        protected static void CheckTokenTypeNotNext(ScriptLoadingContext lcontext, TokenType tokenType)
        {
            Token t = lcontext.Lexer.Current;
            if (t.Type != tokenType)
                UnexpectedTokenType(t);
        }

        protected static Token CheckMatch(ScriptLoadingContext lcontext, Token originalToken, TokenType expectedTokenType, string expectedTokenText)
        {
            Token t = lcontext.Lexer.Current;
            if (t.Type != expectedTokenType)
                throw new SyntaxErrorException(lcontext.Lexer.Current,
                    "'{0}' expected (to close '{1}' at line {2}) near '{3}'",
                    expectedTokenText, originalToken.Text, originalToken.FromLine, t.Text) {IsPrematureStreamTermination = t.Type == TokenType.Eof};

            lcontext.Lexer.Next();

            return t;
        }
    }
}