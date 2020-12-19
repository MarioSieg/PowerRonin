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

namespace Dreamcast.Json
{
    /// <summary>
    ///     Specifies how dates are formatted when writing JSON text.
    /// </summary>
    public enum DateFormatHandling
    {
        /// <summary>
        ///     Dates are written in the ISO 8601 format, e.g. <c>"2012-03-21T05:40Z"</c>.
        /// </summary>
        IsoDateFormat,

        /// <summary>
        ///     Dates are written in the Microsoft JSON format, e.g. <c>"\/Date(1198908717056)\/"</c>.
        /// </summary>
        MicrosoftDateFormat
    }
}