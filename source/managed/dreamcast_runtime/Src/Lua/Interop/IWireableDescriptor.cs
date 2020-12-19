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

namespace MoonSharp.Interpreter.Interop.BasicDescriptors
{
    /// <summary>
    ///     Interface for descriptors with the capability of being serialized
    ///     for later hardwiring.
    /// </summary>
    public interface IWireableDescriptor
    {
        /// <summary>
        ///     Prepares the descriptor for hard-wiring.
        ///     The descriptor fills the passed table with all the needed data for hardwire generators to generate the appropriate
        ///     code.
        /// </summary>
        /// <param name="t">The table to be filled</param>
        void PrepareForWiring(Table t);
    }
}