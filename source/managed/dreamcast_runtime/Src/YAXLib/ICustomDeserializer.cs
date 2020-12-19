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

namespace YAXLib
{
    /// <summary>
    ///     Defines the interface to all custom deserializers used with YAXLib.
    ///     Note that normally you don't need to implement all the methods.
    /// </summary>
    /// <typeparam name="T">
    ///     The type of field, property, class, or struct for which custom deserializer
    ///     is provided
    /// </typeparam>
    public interface ICustomDeserializer<T>
    {
    }
}