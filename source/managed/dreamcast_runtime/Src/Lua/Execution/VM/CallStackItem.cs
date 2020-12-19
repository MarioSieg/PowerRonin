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

using Dreamcast.Lua.Interpreter.Debugging;

namespace Dreamcast.Lua.Interpreter.Execution.VM
{
    internal class CallStackItem
    {
        public int BasePointer;

        public SourceRef CallingSourceRef;
        public ClosureContext ClosureScope;

        public CallbackFunction ClrFunction;
        public CallbackFunction Continuation;
        public int Debug_EntryPoint;
        public SymbolRef[] Debug_Symbols;
        public CallbackFunction ErrorHandler;
        public DynValue ErrorHandlerBeforeUnwind;

        public CallStackItemFlags Flags;
        public DynValue[] LocalScope;
        public int ReturnAddress;
    }
}