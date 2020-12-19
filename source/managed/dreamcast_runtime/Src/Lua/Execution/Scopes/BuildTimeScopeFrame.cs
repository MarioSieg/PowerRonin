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

using MoonSharp.Interpreter.Tree.Statements;

namespace MoonSharp.Interpreter.Execution.Scopes
{
    internal class BuildTimeScopeFrame
    {
        private readonly RuntimeScopeFrame m_ScopeFrame = new();
        private BuildTimeScopeBlock m_ScopeTreeHead;
        private readonly BuildTimeScopeBlock m_ScopeTreeRoot;

        internal BuildTimeScopeFrame(bool hasVarArgs)
        {
            HasVarArgs = hasVarArgs;
            m_ScopeTreeHead = m_ScopeTreeRoot = new BuildTimeScopeBlock(null);
        }

        public bool HasVarArgs { get; }

        internal void PushBlock()
        {
            m_ScopeTreeHead = m_ScopeTreeHead.AddChild();
        }

        internal RuntimeScopeBlock PopBlock()
        {
            var tree = m_ScopeTreeHead;

            m_ScopeTreeHead.ResolveGotos();

            m_ScopeTreeHead = m_ScopeTreeHead.Parent;

            if (m_ScopeTreeHead == null)
                throw new InternalErrorException("Can't pop block - stack underflow");

            return tree.ScopeBlock;
        }

        internal RuntimeScopeFrame GetRuntimeFrameData()
        {
            if (m_ScopeTreeHead != m_ScopeTreeRoot)
                throw new InternalErrorException("Misaligned scope frames/blocks!");

            m_ScopeFrame.ToFirstBlock = m_ScopeTreeRoot.ScopeBlock.To;

            return m_ScopeFrame;
        }

        internal SymbolRef Find(string name)
        {
            for (var tree = m_ScopeTreeHead; tree != null; tree = tree.Parent)
            {
                SymbolRef l = tree.Find(name);

                if (l != null)
                    return l;
            }

            return null;
        }

        internal SymbolRef DefineLocal(string name)
        {
            return m_ScopeTreeHead.Define(name);
        }

        internal SymbolRef TryDefineLocal(string name)
        {
            if (m_ScopeTreeHead.Find(name) != null) m_ScopeTreeHead.Rename(name);

            return m_ScopeTreeHead.Define(name);
        }

        internal void ResolveLRefs()
        {
            m_ScopeTreeRoot.ResolveGotos();

            m_ScopeTreeRoot.ResolveLRefs(this);
        }

        internal int AllocVar(SymbolRef var)
        {
            var.i_Index = m_ScopeFrame.DebugSymbols.Count;
            m_ScopeFrame.DebugSymbols.Add(var);
            return var.i_Index;
        }

        internal int GetPosForNextVar()
        {
            return m_ScopeFrame.DebugSymbols.Count;
        }

        internal void DefineLabel(LabelStatement label)
        {
            m_ScopeTreeHead.DefineLabel(label);
        }

        internal void RegisterGoto(GotoStatement gotostat)
        {
            m_ScopeTreeHead.RegisterGoto(gotostat);
        }
    }
}