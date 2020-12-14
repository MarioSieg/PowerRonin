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

#include "../../include/dce/core/kernel.hpp"
#include "mono_headers.hpp"

namespace dce::scripting {
	class Scripting final : public core::ISubsystem {
	public:
		/* Constructors, assignment operators, destructor */
		Scripting();
		Scripting(const Scripting&) = delete;
		Scripting(Scripting&&) = delete;
		auto operator=(const Scripting&)->Scripting & = delete;
		auto operator=(Scripting&&)->Scripting & = delete;
		~Scripting() override = default;

	private:
		/* Required kernel events */
		static constexpr auto EVENTS = core::ServiceEvents::ALL;

		/* Kernel events */
		virtual auto on_pre_startup([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_post_startup([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_pre_tick([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_post_tick([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_pre_shutdown([[maybe_unused]] Runtime& _rt) -> bool override;
		virtual auto on_post_shutdown([[maybe_unused]] Runtime& _rt) -> bool override;
		
		MonoDomain* domain_ = nullptr;
		MonoAssembly* engine_runtime_ = nullptr;
		MonoImage* engine_image_ = nullptr;
		MonoClass* engine_class_ = nullptr;
		MonoObject* engine_instance_ = nullptr;
		MonoMethod* engine_on_start_ = nullptr;
		MonoMethod* engine_on_update_ = nullptr;
		MonoMethod* engine_on_end_ = nullptr;
	};
}
