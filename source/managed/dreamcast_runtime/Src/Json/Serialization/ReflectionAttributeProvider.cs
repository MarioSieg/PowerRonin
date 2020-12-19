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
using System.Collections.Generic;
using System.Reflection;
using Dreamcast.Json.Utilities;

namespace Dreamcast.Json.Serialization
{
    /// <summary>
    ///     Provides methods to get attributes from a <see cref="System.Type" />, <see cref="MemberInfo" />,
    ///     <see cref="ParameterInfo" /> or <see cref="Assembly" />.
    /// </summary>
    public class ReflectionAttributeProvider : IAttributeProvider
    {
        private readonly object _attributeProvider;

        /// <summary>
        ///     Initializes a new instance of the <see cref="ReflectionAttributeProvider" /> class.
        /// </summary>
        /// <param name="attributeProvider">
        ///     The instance to get attributes for. This parameter should be a
        ///     <see cref="System.Type" />, <see cref="MemberInfo" />, <see cref="ParameterInfo" /> or <see cref="Assembly" />.
        /// </param>
        public ReflectionAttributeProvider(object attributeProvider)
        {
            ValidationUtils.ArgumentNotNull(attributeProvider, nameof(attributeProvider));
            _attributeProvider = attributeProvider;
        }

        /// <summary>
        ///     Returns a collection of all of the attributes, or an empty collection if there are no attributes.
        /// </summary>
        /// <param name="inherit">When <c>true</c>, look up the hierarchy chain for the inherited custom attribute.</param>
        /// <returns>A collection of <see cref="Attribute" />s, or an empty collection.</returns>
        public IList<Attribute> GetAttributes(bool inherit)
        {
            return ReflectionUtils.GetAttributes(_attributeProvider, null, inherit);
        }

        /// <summary>
        ///     Returns a collection of attributes, identified by type, or an empty collection if there are no attributes.
        /// </summary>
        /// <param name="attributeType">The type of the attributes.</param>
        /// <param name="inherit">When <c>true</c>, look up the hierarchy chain for the inherited custom attribute.</param>
        /// <returns>A collection of <see cref="Attribute" />s, or an empty collection.</returns>
        public IList<Attribute> GetAttributes(Type attributeType, bool inherit)
        {
            return ReflectionUtils.GetAttributes(_attributeProvider, attributeType, inherit);
        }
    }
}