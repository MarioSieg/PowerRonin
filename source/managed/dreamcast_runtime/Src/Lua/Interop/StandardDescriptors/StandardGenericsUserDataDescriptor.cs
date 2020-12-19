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
using Dreamcast.Lua.Interpreter.Compatibility;

namespace Dreamcast.Lua.Interpreter.Interop
{
    /// <summary>
    ///     Standard user data descriptor used to instantiate generics.
    /// </summary>
    public class StandardGenericsUserDataDescriptor : IUserDataDescriptor, IGeneratorUserDataDescriptor
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="StandardUserDataDescriptor" /> class.
        /// </summary>
        /// <param name="type">The type this descriptor refers to.</param>
        /// <param name="accessMode">The interop access mode this descriptor uses for members access</param>
        public StandardGenericsUserDataDescriptor(Type type, InteropAccessMode accessMode)
        {
            if (accessMode == InteropAccessMode.NoReflectionAllowed)
                throw new ArgumentException("Can't create a StandardGenericsUserDataDescriptor under a NoReflectionAllowed access mode");

            AccessMode = accessMode;
            Type = type;
            Name = "@@" + type.FullName;
        }

        /// <summary>
        ///     Gets the interop access mode this descriptor uses for members access
        /// </summary>
        public InteropAccessMode AccessMode { get; }

        /// <inheritdoc />
        public IUserDataDescriptor Generate(Type type)
        {
            if (UserData.IsTypeRegistered(type))
                return null;

            if (Framework.Do.IsGenericTypeDefinition(type))
                return null;

            return UserData.RegisterType(type, AccessMode);
        }


        /// <inheritdoc />
        public string Name { get; }

        /// <inheritdoc />
        public Type Type { get; }

        /// <inheritdoc />
        public DynValue Index(Script script, object obj, DynValue index, bool isDirectIndexing)
        {
            return null;
        }

        /// <inheritdoc />
        public bool SetIndex(Script script, object obj, DynValue index, DynValue value, bool isDirectIndexing)
        {
            return false;
        }

        /// <inheritdoc />
        public string AsString(object obj)
        {
            return obj.ToString();
        }

        /// <inheritdoc />
        public DynValue MetaIndex(Script script, object obj, string metaname)
        {
            return null;
        }

        /// <inheritdoc />
        public bool IsTypeCompatible(Type type, object obj)
        {
            return Framework.Do.IsInstanceOfType(type, obj);
        }
    }
}