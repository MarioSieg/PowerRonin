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

namespace Dreamcast.Lua.Interpreter.Serialization.Json
{
    /// <summary>
    ///     UserData representing a null value in a table converted from Json
    /// </summary>
    public sealed class JsonNull
    {
        public static bool isNull()
        {
            return true;
        }

        [Dreamcast.LuaHidden]
        public static bool IsJsonNull(DynValue v)
        {
            return v.Type == DataType.UserData &&
                   v.UserData.Descriptor != null &&
                   v.UserData.Descriptor.Type == typeof(JsonNull);
        }

        [Dreamcast.LuaHidden]
        public static DynValue Create()
        {
            return UserData.CreateStatic<JsonNull>();
        }
    }
}