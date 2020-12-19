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

namespace MoonSharp.Interpreter.Interop
{
    /// <summary>
    ///     Interface for proxy objects (type unsafe version)
    /// </summary>
    public interface IProxyFactory
    {
        /// <summary>
        ///     Gets the proxied type
        /// </summary>
        Type TargetType { get; }

        /// <summary>
        ///     Gets the proxy type
        /// </summary>
        Type ProxyType { get; }

        /// <summary>
        ///     Takes an instance of a target object and returns a proxy object wrapping it
        /// </summary>
        object CreateProxyObject(object o);
    }

    /// <summary>
    ///     Interface for proxy objects (type safe version)
    /// </summary>
    /// <typeparam name="TProxy">The type of the proxy.</typeparam>
    /// <typeparam name="TTarget">The type of the target.</typeparam>
    public interface IProxyFactory<TProxy, TTarget> : IProxyFactory
        where TProxy : class
        where TTarget : class
    {
        /// <summary>
        ///     Takes an instance of a target object and returns a proxy object wrapping it
        /// </summary>
        TProxy CreateProxyObject(TTarget target);
    }
}