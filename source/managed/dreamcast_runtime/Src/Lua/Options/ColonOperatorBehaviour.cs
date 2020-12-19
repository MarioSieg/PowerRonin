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

namespace Dreamcast.Lua.Interpreter
{
    /// <summary>
    ///     Defines behaviour of the colon ':' operator in CLR callbacks.
    ///     Default behaviour is for ':' being treated the same as a '.' if the functions is implemented on the CLR side (e.g.
    ///     in C#).
    /// </summary>
    public enum ColonOperatorBehaviour
    {
        /// <summary>
        ///     The colon is treated the same as the dot ('.') operator.
        /// </summary>
        TreatAsDot,

        /// <summary>
        ///     The colon is treated the same as the dot ('.') operator if the first argument is userdata, as a Lua colon operator
        ///     otherwise.
        /// </summary>
        TreatAsDotOnUserData,

        /// <summary>
        ///     The colon is treated in the same as the Lua colon operator works.
        /// </summary>
        TreatAsColon
    }
}