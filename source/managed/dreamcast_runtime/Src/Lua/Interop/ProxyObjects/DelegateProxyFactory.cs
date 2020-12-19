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
    ///     Implementation of IProxyFactory taking two delegates for simple instancing of proxies.
    /// </summary>
    /// <typeparam name="TProxy">The type of the proxy.</typeparam>
    /// <typeparam name="TTarget">The type of the target.</typeparam>
    public class DelegateProxyFactory<TProxy, TTarget> : IProxyFactory<TProxy, TTarget>
        where TProxy : class
        where TTarget : class
    {
        private readonly Func<TTarget, TProxy> wrapDelegate;

        /// <summary>
        ///     Initializes a new instance of the <see cref="DelegateProxyFactory{TProxy, TTarget}" /> class.
        /// </summary>
        /// <param name="wrapDelegate">The proxy.</param>
        /// <param name="unwrapDelegate">The deproxy.</param>
        public DelegateProxyFactory(Func<TTarget, TProxy> wrapDelegate)
        {
            this.wrapDelegate = wrapDelegate;
        }

        /// <summary>
        ///     Takes an instance of a target object and returns a proxy object wrapping it
        /// </summary>
        public TProxy CreateProxyObject(TTarget target)
        {
            return wrapDelegate(target);
        }

        /// <summary>
        ///     Takes an instance of a target object and returns a proxy object wrapping it
        /// </summary>
        /// <param name="o"></param>
        /// <returns></returns>
        public object CreateProxyObject(object o)
        {
            return CreateProxyObject((TTarget) o);
        }

        /// <summary>
        ///     Gets the proxied type
        /// </summary>
        /// <returns></returns>
        public Type TargetType => typeof(TTarget);

        /// <summary>
        ///     Gets the proxy type
        /// </summary>
        public Type ProxyType => typeof(TProxy);
    }
}