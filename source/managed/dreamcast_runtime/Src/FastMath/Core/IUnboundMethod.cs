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

namespace FastMath.Core
{
    /// <summary>
    ///     Method that could be calculated with any argument, but with a bit lower performance
    /// </summary>
    public interface IUnboundMethod : IMemoizedMethod
    {
        /// <summary>
        ///     Calculates method with any argument. Has a bit less performance than original calculate method
        ///     Be care to use this method with very small or big arguments - possible accuracy problems
        /// </summary>
        float CalculateUnbound(float argument);
    }
}