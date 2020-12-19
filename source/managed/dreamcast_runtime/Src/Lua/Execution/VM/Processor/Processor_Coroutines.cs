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

using System;

namespace MoonSharp.Interpreter.Execution.VM
{
    // This part is practically written procedural style - it looks more like C than C#.
    // This is intentional so to avoid this-calls and virtual-calls as much as possible.
    // Same reason for the "sealed" declaration.
    internal sealed partial class Processor
    {
        public CoroutineState State { get; private set; }

        public Coroutine AssociatedCoroutine { get; set; }

        public DynValue Coroutine_Create(Closure closure)
        {
            // create a processor instance
            Processor P = new(this);

            // Put the closure as first value on the stack, for future reference
            P.m_ValueStack.Push(DynValue.NewClosure(closure));

            // Return the coroutine handle
            return DynValue.NewCoroutine(new Coroutine(P));
        }

        public DynValue Coroutine_Resume(DynValue[] args)
        {
            EnterProcessor();

            try
            {
                var entrypoint = 0;

                if (State != CoroutineState.NotStarted && State != CoroutineState.Suspended && State != CoroutineState.ForceSuspended)
                    throw ScriptRuntimeException.CannotResumeNotSuspended(State);

                if (State == CoroutineState.NotStarted)
                {
                    entrypoint = PushClrToScriptStackFrame(CallStackItemFlags.ResumeEntryPoint, null, args);
                }
                else if (State == CoroutineState.Suspended)
                {
                    m_ValueStack.Push(DynValue.NewTuple(args));
                    entrypoint = m_SavedInstructionPtr;
                }
                else if (State == CoroutineState.ForceSuspended)
                {
                    if (args != null && args.Length > 0)
                        throw new ArgumentException("When resuming a force-suspended coroutine, args must be empty.");

                    entrypoint = m_SavedInstructionPtr;
                }

                State = CoroutineState.Running;
                DynValue retVal = Processing_Loop(entrypoint);

                if (retVal.Type == DataType.YieldRequest)
                {
                    if (retVal.YieldRequest.Forced)
                    {
                        State = CoroutineState.ForceSuspended;
                        return retVal;
                    }
                    else
                    {
                        State = CoroutineState.Suspended;
                        return DynValue.NewTuple(retVal.YieldRequest.ReturnValues);
                    }
                }
                else
                {
                    State = CoroutineState.Dead;
                    return retVal;
                }
            }
            catch (Exception)
            {
                // Unhandled exception - move to dead
                State = CoroutineState.Dead;
                throw;
            }
            finally
            {
                LeaveProcessor();
            }
        }
    }
}