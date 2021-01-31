// // *******************************************************************************
// // The content of this file includes portions of the KerboGames Power Ronin Technology
// // released in source code form as part of the SDK package.
// // 
// // Commercial License Usage
// // 
// // Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// // may use this file in accordance with the end user license agreement provided 
// // with the software or, alternatively, in accordance with the terms contained in a
// // written agreement between you and KerboGames.
// // 
// // Copyright (c) 2013-2021 KerboGames, MarioSieg.
// // support@kerbogames.com
// // *******************************************************************************

#pragma once

#include "serial.hpp"
#include "csinterop.hpp"

namespace PowerRonin
{
	enum class GraphicsBackend: CSharp::$byte CSHARP_HYBRID_INTEROP("Dreamcast.Core.GraphicsAPI")
	{
		Direct3D11 = 0,
		Direct3D12 = 1,
		Metal = 2,
		OpenGl = 3,
		Vulkan = 4
	};

	enum class MsaaMode: CSharp::$byte CSHARP_HYBRID_INTEROP("Dreamcast.Core.MsaaMode")
	{
		Off = 1,
		X2 = 2,
		X4 = 4,
		X8 = 8,
		X16 = 16
	};
	
	struct DisplayConfig final CSHARP_HYBRID_INTEROP("Dreamcast.Core.DisplayConfig")
	{
		CSharp::$bool IsFullScreen;
		CSharp::$bool IsMaximized;
		CSharp::$Size2 Resolution;
		CSharp::$bool VSync;
		CSharp::$ushort MaxFrameRate;
	};

	struct EditorConfig final CSHARP_HYBRID_INTEROP("Dreamcast.Core.EditorConfig")
	{
		CSharp::$byte CustomFontSize;
		CSharp::$byte AutoFontSizeFullHD;
		CSharp::$byte AutoFontSizeWideQuadHD;
		CSharp::$byte AutoFontSizeUltraHD;
		CSharp::$bool EnableAutoFontSize;
		CSharp::$bool EnableFontAntiAliasing;
		CSharp::$float Alpha;
		CSharp::$float Rounding;
		CSharp::$bool ShowTerminal;
		CSharp::$bool ShowStats;
		CSharp::$bool ShowMatrixStats;
		CSharp::$byte StatsTextColor;
		CSharp::$bool ShowBigStats;
		CSharp::$bool ShowGrid;
		CSharp::$float GridSize;
		CSharp::$Vector3 GridOriginCenter;
		CSharp::$bool ShowGizmos;
	};

	struct GraphicsConfig final CSHARP_HYBRID_INTEROP("Dreamcast.Core.EditorConfig")
	{
		GraphicsBackend GraphicsApi;
		MsaaMode MsaaMode;
		CSharp::$bool EnableHighDpiMode;
		CSharp::$bool EnableSrgbMode;
		CSharp::$bool EnableHdr10;
		CSharp::$bool EnableMaxAnisotropy;
	};

	struct ScriptingConfig final
	{
		std::filesystem::path ConfigDir = "runtime/etc";
		std::filesystem::path LibraryDir = "runtime/lib";
	};

	struct AppConfig final
	{
		std::string AppName = {};
		std::string AppCompany = {};
	};

	class SystemConfig final
	{
	public:
		DisplayConfig Display = {};
		EditorConfig Editor = {};
		GraphicsConfig Graphics = {};
		ScriptingConfig Scripting = {};
		AppConfig App = {};
	};
} // namespace PowerRonin // namespace PowerRonin
