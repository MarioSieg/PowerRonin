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

#pragma once

namespace dce {
	class IEventBehaviour {
	public:
		IEventBehaviour() noexcept = default;
		IEventBehaviour(const IEventBehaviour&) noexcept = default;
		IEventBehaviour(IEventBehaviour&&) noexcept = default;
		auto operator=(const IEventBehaviour&) noexcept -> IEventBehaviour& = default ;
		auto operator=(IEventBehaviour&&) noexcept -> IEventBehaviour& = default;
		virtual ~IEventBehaviour() = default;

		virtual void start();
		virtual void update();
		virtual void end();
	};
} // namespace dce // namespace dce
