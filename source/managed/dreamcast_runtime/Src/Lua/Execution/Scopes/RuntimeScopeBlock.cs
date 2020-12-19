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

namespace Dreamcast.Lua.Interpreter.Execution
{
    internal class RuntimeScopeBlock
    {
        public int From { get; internal set; }
        public int To { get; internal set; }
        public int ToInclusive { get; internal set; }

        public override string ToString()
        {
            return string.Format("ScopeBlock : {0} -> {1} --> {2}", From, To, ToInclusive);
        }
    }
}