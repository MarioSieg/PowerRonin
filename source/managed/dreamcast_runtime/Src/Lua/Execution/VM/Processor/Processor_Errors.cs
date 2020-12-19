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
    internal sealed partial class Processor
    {
        private SourceRef GetCurrentSourceRef(int instructionPtr)
        {
            if (instructionPtr >= 0 && instructionPtr < m_RootChunk.Code.Count) return m_RootChunk.Code[instructionPtr].SourceCodeRef;
            return null;
        }


        private void FillDebugData(InterpreterException ex, int ip)
        {
            // adjust IP
            if (ip == YIELD_SPECIAL_TRAP)
                ip = m_SavedInstructionPtr;
            else
                ip -= 1;

            ex.InstructionPtr = ip;

            SourceRef sref = GetCurrentSourceRef(ip);

            ex.DecorateMessage(m_Script, sref, ip);

            ex.CallStack = Debugger_GetCallStack(sref);
        }
    }
}