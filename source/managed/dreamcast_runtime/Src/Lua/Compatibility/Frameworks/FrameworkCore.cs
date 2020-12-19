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

#if DOTNET_CORE
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Dreamcast.Lua.Interpreter.Compatibility.Frameworks
{
	class FrameworkCurrent : FrameworkClrBase
	{
		public override Type GetInterface(Type type, string name)
		{
			return type.GetTypeInfo().GetInterface(name);
		}

		public override TypeInfo GetTypeInfoFromType(Type t)
		{
			return t.GetTypeInfo();
		}

		public override bool IsDbNull(object o)
		{
			return o != null && o.GetType().FullName.StartsWith("System.DBNull");
		}

		public override bool StringContainsChar(string str, char chr)
		{
			return str.Contains(chr);
		}
	}
}
#endif