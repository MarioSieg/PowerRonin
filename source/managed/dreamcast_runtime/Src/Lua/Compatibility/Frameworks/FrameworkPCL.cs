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

#if !(DOTNET_CORE || NETFX_CORE) && PCL
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MoonSharp.Interpreter.Compatibility.Frameworks
{
	class FrameworkCurrent : FrameworkClrBase
	{
		public override Type GetTypeInfoFromType(Type t)
		{
			return t;
		}

		public override bool IsDbNull(object o)
		{
			return o != null && o.GetType().FullName.StartsWith("System.DBNull");
		}

		public override bool StringContainsChar(string str, char chr)
		{
			return str.Contains(chr.ToString());
		}

		public override Type GetInterface(Type type, string name)
		{
			return type.GetInterfaces().
				FirstOrDefault(t => t.Name == name);
		}
	}
}

#endif