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
using System.Runtime.Serialization;

namespace Dreamcast.Json.Serialization
{
    internal class SerializationBinderAdapter : ISerializationBinder
    {
#pragma warning disable 618
        public readonly SerializationBinder SerializationBinder;
#pragma warning restore 618

#pragma warning disable 618
        public SerializationBinderAdapter(SerializationBinder serializationBinder)
        {
            SerializationBinder = serializationBinder;
        }
#pragma warning restore 618

        public Type BindToType(string? assemblyName, string typeName)
        {
            return SerializationBinder.BindToType(assemblyName, typeName);
        }

        public void BindToName(Type serializedType, out string? assemblyName, out string? typeName)
        {
#if HAVE_SERIALIZATION_BINDER_BIND_TO_NAME
            SerializationBinder.BindToName(serializedType, out assemblyName, out typeName);
#else
            assemblyName = null;
            typeName = null;
#endif
        }
    }
}