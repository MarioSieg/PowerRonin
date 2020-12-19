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

namespace MoonSharp.Interpreter.Interop.RegistrationPolicies
{
    /// <summary>
    ///     Similar to <see cref="DefaultRegistrationPolicy" />, but with automatic type registration is disabled.
    /// </summary>
    public class AutomaticRegistrationPolicy : DefaultRegistrationPolicy
    {
        /// <summary>
        ///     Allows type automatic registration for the specified type.
        ///     NOTE: automatic type registration is NOT recommended.
        /// </summary>
        /// <param name="type">The type.</param>
        /// <returns>
        ///     True to register the type automatically, false otherwise.
        /// </returns>
        public override bool AllowTypeAutoRegistration(Type type)
        {
            return true;
        }
    }
}