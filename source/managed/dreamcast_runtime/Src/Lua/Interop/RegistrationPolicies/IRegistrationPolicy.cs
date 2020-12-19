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

namespace Dreamcast.Lua.Interpreter.Interop.RegistrationPolicies
{
    /// <summary>
    ///     Interface for managing how to handle
    /// </summary>
    public interface IRegistrationPolicy
    {
        /// <summary>
        ///     Called to handle the registration or deregistration of a type descriptor. Must return the type descriptor to be
        ///     registered, or null to remove the registration.
        /// </summary>
        /// <param name="newDescriptor">The new descriptor, or null if this is a deregistration.</param>
        /// <param name="oldDescriptor">The old descriptor, or null if no descriptor was previously registered for this type.</param>
        /// <returns></returns>
        IUserDataDescriptor HandleRegistration(IUserDataDescriptor newDescriptor, IUserDataDescriptor oldDescriptor);

        /// <summary>
        ///     Allows type automatic registration for the specified type.
        ///     NOTE: automatic type registration is NOT recommended.
        /// </summary>
        /// <param name="type">The type.</param>
        /// <returns>True to register the type automatically, false otherwise.</returns>
        bool AllowTypeAutoRegistration(Type type);
    }
}