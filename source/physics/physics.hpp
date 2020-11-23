// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: physics.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 17.11.2020 10:05

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
		static constexpr auto EVENTS = core::ServiceEvents::PRE_STARTUP | core::ServiceEvents::POST_TICK | core::ServiceEvents::PRE_SHUTDOWN;

		/* Kernel events */
		virtual auto on_pre_startup([[maybe_unused]] State&) -> bool override;
		virtual auto on_post_tick(State&) -> bool override;
		virtual auto on_pre_shutdown([[maybe_unused]] State&) -> bool override;

		/* Main handles */
		btDefaultCollisionConfiguration* collision_configuration_ = nullptr;
		btCollisionDispatcher* dispatcher_ = nullptr;
		btBroadphaseInterface* broadphase_interface_ = nullptr;
		btSequentialImpulseConstraintSolver* solver_ = nullptr;
		btDiscreteDynamicsWorld* dynamics_world_ = nullptr;
		btAlignedObjectArray<btCollisionShape*> collsion_shapes_ = {};
	};
}
