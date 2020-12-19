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

using MoonSharp.Interpreter.DataStructs;

namespace MoonSharp.Interpreter.Execution.VM
{
    internal sealed class ExecutionState
    {
        public FastStack<CallStackItem> ExecutionStack = new(131072);
        public int InstructionPtr = 0;
        public CoroutineState State = CoroutineState.NotStarted;
        public FastStack<DynValue> ValueStack = new(131072);
    }
}