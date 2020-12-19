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
using Dreamcast.Lua.Interpreter.Interop.RegistrationPolicies;

namespace Dreamcast.Lua.Interpreter.Interop
{
    /// <summary>
    ///     Collection of the standard policies to handle UserData type registrations.
    ///     Provided mostly for compile-time backward compatibility with old code.
    ///     See also : <see cref="IRegistrationPolicy" /> .
    /// </summary>
    public static class InteropRegistrationPolicy
    {
        /// <summary>
        ///     The default registration policy used by Dreamcast.Lua unless explicitely replaced.
        ///     Deregistrations are allowed, but registration of a new descriptor are not allowed
        ///     if a descriptor is already registered for that type.
        ///     Types must be explicitly registered.
        /// </summary>
        public static IRegistrationPolicy Default => new DefaultRegistrationPolicy();

        /// <summary>
        ///     The default registration policy used by Dreamcast.Lua unless explicitely replaced.
        ///     Deregistrations are allowed, but registration of a new descriptor are not allowed
        ///     if a descriptor is already registered for that type.
        ///     Types must be explicitly registered.
        /// </summary>
        [Obsolete("Please use InteropRegistrationPolicy.Default instead.")]
        public static IRegistrationPolicy Explicit => new DefaultRegistrationPolicy();

        /// <summary>
        ///     Types are automatically registered if not found in the registry. This is easier to use but potentially unsafe.
        /// </summary>
        public static IRegistrationPolicy Automatic => new AutomaticRegistrationPolicy();
    }
}