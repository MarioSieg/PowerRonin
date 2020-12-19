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
using Dreamcast.Lua.Interpreter.Tree.Expressions;
using Dreamcast.Lua.Interpreter.Tree.Statements;

namespace Dreamcast.Lua.Interpreter.Tree
{
    internal abstract class Statement : NodeBase
    {
        public Statement(ScriptLoadingContext lcontext)
            : base(lcontext)
        {
        }


        protected static Statement CreateStatement(ScriptLoadingContext lcontext, out bool forceLast)
        {
            Token tkn = lcontext.Lexer.Current;

            forceLast = false;

            switch (tkn.Type)
            {
                case TokenType.DoubleColon:
                    return new LabelStatement(lcontext);
                case TokenType.Goto:
                    return new GotoStatement(lcontext);
                case TokenType.SemiColon:
                    lcontext.Lexer.Next();
                    return new EmptyStatement(lcontext);
                case TokenType.If:
                    return new IfStatement(lcontext);
                case TokenType.While:
                    return new WhileStatement(lcontext);
                case TokenType.Do:
                    return new ScopeBlockStatement(lcontext);
                case TokenType.For:
                    return DispatchForLoopStatement(lcontext);
                case TokenType.Repeat:
                    return new RepeatStatement(lcontext);
                case TokenType.Function:
                    return new FunctionDefinitionStatement(lcontext, false, null);
                case TokenType.Local:
                    Token localToken = lcontext.Lexer.Current;
                    lcontext.Lexer.Next();
                    if (lcontext.Lexer.Current.Type == TokenType.Function)
                        return new FunctionDefinitionStatement(lcontext, true, localToken);
                    else
                        return new AssignmentStatement(lcontext, localToken);
                case TokenType.Return:
                    forceLast = true;
                    return new ReturnStatement(lcontext);
                case TokenType.Break:
                    return new BreakStatement(lcontext);
                default:
                {
                    Token l = lcontext.Lexer.Current;
                    Expression exp = Expression.PrimaryExp(lcontext);
                    FunctionCallExpression fnexp = exp as FunctionCallExpression;

                    if (fnexp != null)
                        return new FunctionCallStatement(lcontext, fnexp);
                    return new AssignmentStatement(lcontext, exp, l);
                }
            }
        }

        private static Statement DispatchForLoopStatement(ScriptLoadingContext lcontext)
        {
            //	for Name ‘=’ exp ‘,’ exp [‘,’ exp] do block end | 
            //	for namelist in explist do block end | 		

            Token forTkn = CheckTokenType(lcontext, TokenType.For);

            Token name = CheckTokenType(lcontext, TokenType.Name);

            if (lcontext.Lexer.Current.Type == TokenType.Op_Assignment)
                return new ForLoopStatement(lcontext, name, forTkn);
            return new ForEachLoopStatement(lcontext, name, forTkn);
        }
    }
}