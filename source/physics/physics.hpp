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
#include "physics_headers.hpp"

namespace dce::physics {
	class Physics final : public core::ISubsystem {
	public:
		/* Constructors, assignment operators, destructor */
		Physics();
		Physics(const Physics&) = delete;
		Physics(Physics&&) = delete;
		auto operator=(const Physics&) -> Physics& = delete;
		auto operator=(Physics&&) -> Physics& = delete;
		~Physics() override = default;

	private:
		/* Required kernel events */
		static constexpr auto EVENTS = core::ServiceEvents::PRE_STARTUP | core::ServiceEvents::POST_TICK |
			core::ServiceEvents::PRE_SHUTDOWN;

		/* Kernel events */
		virtual auto on_pre_startup([[maybe_unused]] Runtime&) -> bool override;
		virtual auto on_post_tick(Runtime&) -> bool override;
		virtual auto on_pre_shutdown([[maybe_unused]] Runtime&) -> bool override;

		/* Main handles */
		btDefaultCollisionConfiguration* collision_configuration_ = nullptr;
		btCollisionDispatcher* dispatcher_ = nullptr;
		btBroadphaseInterface* broadphase_interface_ = nullptr;
		btSequentialImpulseConstraintSolver* solver_ = nullptr;
		btDiscreteDynamicsWorld* dynamics_world_ = nullptr;
		btAlignedObjectArray<btCollisionShape*> collsion_shapes_ = {};
	};
}
