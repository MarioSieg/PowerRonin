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

using System.Collections.Generic;
using MoonSharp.Interpreter.Debugging;

namespace MoonSharp.Interpreter.Execution.VM
{
    internal sealed partial class Processor
    {
        private class DebugContext
        {
            public readonly List<SourceRef> BreakPoints = new();
            public IDebugger DebuggerAttached;
            public DebuggerAction.ActionType DebuggerCurrentAction = DebuggerAction.ActionType.None;
            public int DebuggerCurrentActionTarget = -1;
            public bool DebuggerEnabled = true;
            public int ExStackDepthAtStep = -1;
            public SourceRef LastHlRef;
            public bool LineBasedBreakPoints;
        }
    }
}