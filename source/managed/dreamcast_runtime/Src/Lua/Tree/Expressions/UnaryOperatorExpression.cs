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

namespace Dreamcast.Lua.Interpreter.Tree.Expressions
{
    internal class UnaryOperatorExpression : Expression
    {
        private readonly Expression m_Exp;
        private readonly string m_OpText;

        public UnaryOperatorExpression(ScriptLoadingContext lcontext, Expression subExpression, Token unaryOpToken)
            : base(lcontext)
        {
            m_OpText = unaryOpToken.Text;
            m_Exp = subExpression;
        }


        public override void Compile(ByteCode bc)
        {
            m_Exp.Compile(bc);

            switch (m_OpText)
            {
                case "not":
                    bc.Emit_Operator(OpCode.Not);
                    break;
                case "#":
                    bc.Emit_Operator(OpCode.Len);
                    break;
                case "-":
                    bc.Emit_Operator(OpCode.Neg);
                    break;
                default:
                    throw new InternalErrorException("Unexpected unary operator '{0}'", m_OpText);
            }
        }

        public override DynValue Eval(ScriptExecutionContext context)
        {
            DynValue v = m_Exp.Eval(context).ToScalar();

            switch (m_OpText)
            {
                case "not":
                    return DynValue.NewBoolean(!v.CastToBool());
                case "#":
                    return v.GetLength();
                case "-":
                {
                    var d = v.CastToNumber();

                    if (d.HasValue)
                        return DynValue.NewNumber(-d.Value);

                    throw new DynamicExpressionException("Attempt to perform arithmetic on non-numbers.");
                }
                default:
                    throw new DynamicExpressionException("Unexpected unary operator '{0}'", m_OpText);
            }
        }
    }
}