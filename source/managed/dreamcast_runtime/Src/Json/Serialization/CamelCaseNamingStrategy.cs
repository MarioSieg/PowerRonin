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

using Dreamcast.Json.Utilities;

namespace Dreamcast.Json.Serialization
{
    /// <summary>
    ///     A camel case naming strategy.
    /// </summary>
    public class CamelCaseNamingStrategy : NamingStrategy
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="CamelCaseNamingStrategy" /> class.
        /// </summary>
        /// <param name="processDictionaryKeys">
        ///     A flag indicating whether dictionary keys should be processed.
        /// </param>
        /// <param name="overrideSpecifiedNames">
        ///     A flag indicating whether explicitly specified property names should be processed,
        ///     e.g. a property name customized with a <see cref="JsonPropertyAttribute" />.
        /// </param>
        public CamelCaseNamingStrategy(bool processDictionaryKeys, bool overrideSpecifiedNames)
        {
            ProcessDictionaryKeys = processDictionaryKeys;
            OverrideSpecifiedNames = overrideSpecifiedNames;
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="CamelCaseNamingStrategy" /> class.
        /// </summary>
        /// <param name="processDictionaryKeys">
        ///     A flag indicating whether dictionary keys should be processed.
        /// </param>
        /// <param name="overrideSpecifiedNames">
        ///     A flag indicating whether explicitly specified property names should be processed,
        ///     e.g. a property name customized with a <see cref="JsonPropertyAttribute" />.
        /// </param>
        /// <param name="processExtensionDataNames">
        ///     A flag indicating whether extension data names should be processed.
        /// </param>
        public CamelCaseNamingStrategy(bool processDictionaryKeys, bool overrideSpecifiedNames, bool processExtensionDataNames)
            : this(processDictionaryKeys, overrideSpecifiedNames)
        {
            ProcessExtensionDataNames = processExtensionDataNames;
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="CamelCaseNamingStrategy" /> class.
        /// </summary>
        public CamelCaseNamingStrategy()
        {
        }

        /// <summary>
        ///     Resolves the specified property name.
        /// </summary>
        /// <param name="name">The property name to resolve.</param>
        /// <returns>The resolved property name.</returns>
        protected override string ResolvePropertyName(string name)
        {
            return StringUtils.ToCamelCase(name);
        }
    }
}