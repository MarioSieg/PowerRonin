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

using MoonSharp.Interpreter.Interop;
using MoonSharp.Interpreter.Platforms;

namespace MoonSharp.Interpreter
{
    /// <summary>
    ///     Class containing script global options, that is options which cannot be customized per-script.
    ///     <see cref="Script.GlobalOptions" />
    /// </summary>
    public class ScriptGlobalOptions
    {
        internal ScriptGlobalOptions()
        {
            Platform = PlatformAutoDetector.GetDefaultPlatform();
            CustomConverters = new CustomConvertersCollection();
            FuzzySymbolMatching = FuzzySymbolMatchingBehavior.Camelify | FuzzySymbolMatchingBehavior.UpperFirstLetter | FuzzySymbolMatchingBehavior.PascalCase;
        }

        /// <summary>
        ///     Gets or sets the custom converters.
        /// </summary>
        public CustomConvertersCollection CustomConverters { get; set; }

        /// <summary>
        ///     Gets or sets the platform abstraction to use.
        /// </summary>
        /// <value>
        ///     The current platform abstraction.
        /// </value>
        public IPlatformAccessor Platform { get; set; }

        /// <summary>
        ///     Gets or sets a value indicating whether interpreter exceptions should be
        ///     re-thrown as nested exceptions.
        /// </summary>
        public bool RethrowExceptionNested { get; set; }

        /// <summary>
        ///     Gets or sets an enum that controls behaviour when a symbol (method, property, userdata) is not found in a
        ///     userdata's descriptor. For instance,
        ///     when this value is <see cref="FuzzySymbolMatchingBehavior.UpperFirstLetter" /> and Lua code calls the non-existent
        ///     method <c>someuserdata.someMethod()</c>,
        ///     <c>someuserdata.SomeMethod()</c> will also be tried.
        /// </summary>
        public FuzzySymbolMatchingBehavior FuzzySymbolMatching { get; set; }
    }
}