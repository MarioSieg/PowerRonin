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

namespace Dreamcast.Json.Serialization
{
    /// <summary>
    ///     Used by <see cref="JsonSerializer" /> to resolve a <see cref="JsonContract" /> for a given <see cref="Type" />.
    /// </summary>
    /// <example>
    ///     <code lang="cs" source="..\Src\Dreamcast.Json.Tests\Documentation\SerializationTests.cs"
    ///         region="ReducingSerializedJsonSizeContractResolverObject" title="IContractResolver Class" />
    ///     <code lang="cs" source="..\Src\Dreamcast.Json.Tests\Documentation\SerializationTests.cs"
    ///         region="ReducingSerializedJsonSizeContractResolverExample" title="IContractResolver Example" />
    /// </example>
    public interface IContractResolver
    {
        /// <summary>
        ///     Resolves the contract for a given type.
        /// </summary>
        /// <param name="type">The type to resolve a contract for.</param>
        /// <returns>The contract for a given type.</returns>
        JsonContract ResolveContract(Type type);
    }
}