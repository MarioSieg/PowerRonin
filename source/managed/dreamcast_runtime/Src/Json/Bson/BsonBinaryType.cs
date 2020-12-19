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

#nullable disable

namespace Dreamcast.Json.Bson
{
    internal enum BsonBinaryType : byte
    {
        Binary = 0x00,
        Function = 0x01,

        [Obsolete("This type has been deprecated in the BSON specification. Use Binary instead.")]
        BinaryOld = 0x02,

        [Obsolete("This type has been deprecated in the BSON specification. Use Uuid instead.")]
        UuidOld = 0x03,
        Uuid = 0x04,
        Md5 = 0x05,
        UserDefined = 0x80
    }
}