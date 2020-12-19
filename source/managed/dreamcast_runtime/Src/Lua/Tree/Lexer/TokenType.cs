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

namespace MoonSharp.Interpreter.Tree
{
    internal enum TokenType
    {
        Eof,
        HashBang,
        Name,
        And,
        Break,
        Do,
        Else,
        ElseIf,
        End,
        False,
        For,
        Function,
        Lambda,
        Goto,
        If,
        In,
        Local,
        Nil,
        Not,
        Or,
        Repeat,
        Return,
        Then,
        True,
        Until,
        While,
        Op_Equal,
        Op_Assignment,
        Op_LessThan,
        Op_LessThanEqual,
        Op_GreaterThanEqual,
        Op_GreaterThan,
        Op_NotEqual,
        Op_Concat,
        VarArgs,
        Dot,
        Colon,
        DoubleColon,
        Comma,
        Brk_Close_Curly,
        Brk_Open_Curly,
        Brk_Close_Round,
        Brk_Open_Round,
        Brk_Close_Square,
        Brk_Open_Square,
        Op_Len,
        Op_Pwr,
        Op_Mod,
        Op_Div,
        Op_Mul,
        Op_MinusOrSub,
        Op_Add,
        Comment,

        String,
        String_Long,

        Number,
        Number_HexFloat,
        Number_Hex,
        SemiColon,
        Invalid,

        Brk_Open_Curly_Shared,
        Op_Dollar
    }
}