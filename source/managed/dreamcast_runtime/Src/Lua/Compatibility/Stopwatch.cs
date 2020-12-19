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

#if PCL || ((!UNITY_EDITOR) && (ENABLE_DOTNET))
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Diagnostics
{
	internal class Stopwatch
	{
		DateTime startTime, stopTime;

		public void Start() 
		{
			startTime = DateTime.UtcNow;
		}
		
		public void Stop() 
		{
			stopTime = DateTime.UtcNow;
		}

		public static Stopwatch StartNew()
		{
			Stopwatch sw = new Stopwatch();
			sw.Start();
			return sw;
		}

		public long ElapsedMilliseconds
		{
			get
			{
				return (long)((stopTime - startTime).TotalMilliseconds);
			}
		}


	}
}
#endif