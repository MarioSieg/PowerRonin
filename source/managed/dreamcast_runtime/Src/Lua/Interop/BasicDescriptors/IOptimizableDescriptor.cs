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

namespace Dreamcast.Lua.Interpreter.Interop.BasicDescriptors
{
    /// <summary>
    ///     Interface for descriptors of any kind which support optimizations of their implementation according to
    ///     InteropAccessMode
    ///     modes. This should seldom - if ever - be implemented in user code.
    /// </summary>
    public interface IOptimizableDescriptor
    {
        /// <summary>
        ///     Called by standard descriptors when background optimization or preoptimization needs to be performed.
        /// </summary>
        void Optimize();
    }
}