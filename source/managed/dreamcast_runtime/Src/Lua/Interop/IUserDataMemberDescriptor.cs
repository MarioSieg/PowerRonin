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

namespace Dreamcast.Lua.Interpreter.Interop
{
    /// <summary>
    ///     Interface used by standard descriptors to access members of a given type from scripts.
    /// </summary>
    public interface IUserDataMemberDescriptor
    {
        /// <summary>
        ///     Gets the name of the descriptor (usually, the name of the type described).
        /// </summary>
        string Name { get; }

        /// <summary>
        ///     Gets the type this descriptor refers to
        /// </summary>
        Type Type { get; }

        /// <summary>
        ///     Gets the type of the member.
        /// </summary>
        /// <value>
        ///     The type of the member.
        /// </value>
        UserDataMemberType MemberType { get; }


        bool IsStatic { get; }

        /// <summary>
        ///     Gets the value of the member
        /// </summary>
        /// <param name="script">The script.</param>
        /// <param name="obj">The object.</param>
        /// <returns></returns>
        DynValue GetValue(Script script, object obj);

        /// <summary>
        ///     Sets the value of the member
        /// </summary>
        /// <param name="script">The script.</param>
        /// <param name="obj">The object.</param>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        bool SetValue(Script script, object obj, DynValue value);


        void Optimize();
    }
}