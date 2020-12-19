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

#if HAVE_OBSOLETE_FORMATTER_ASSEMBLY_STYLE
namespace System.Runtime.Serialization.Formatters
{
    /// <summary>
    /// Indicates the method that will be used during deserialization for locating and loading assemblies.
    /// </summary>
    [Obsolete("FormatterAssemblyStyle is obsolete. Use TypeNameAssemblyFormatHandling instead.")]
    public enum FormatterAssemblyStyle
    {
        /// <summary>
        /// In simple mode, the assembly used during deserialization need not match exactly the assembly used during serialization. Specifically, the version numbers need not match as the <see cref="M:System.Reflection.Assembly.LoadWithPartialName(String)"/> method is used to load the assembly.
        /// </summary>
        Simple = 0,

        /// <summary>
        /// In full mode, the assembly used during deserialization must match exactly the assembly used during serialization. The <see cref="System.Reflection.Assembly.Load"/> is used to load the assembly.
        /// </summary>
        Full = 1
    }
}

#endif