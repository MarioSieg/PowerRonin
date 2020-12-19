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

namespace Dreamcast.Lua.Interpreter.Interop.BasicDescriptors
{
    /// <summary>
    ///     Permissions for members access
    /// </summary>
    [Flags]
    public enum MemberDescriptorAccess
    {
        /// <summary>
        ///     The member can be read from
        /// </summary>
        CanRead = 1,

        /// <summary>
        ///     The member can be written to
        /// </summary>
        CanWrite = 2,

        /// <summary>
        ///     The can be invoked
        /// </summary>
        CanExecute = 4
    }
}