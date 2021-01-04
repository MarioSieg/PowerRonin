#pragma once

#include "../../include/power_ronin/core/kernel.hpp"
#include "physics_headers.hpp"

namespace power_ronin::physics
{
	class Physics final : public core::ISubsystem
	{
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
		auto on_pre_startup([[maybe_unused]] Runtime&) -> bool override;
		auto on_post_tick(Runtime&) -> bool override;
		auto on_pre_shutdown([[maybe_unused]] Runtime&) -> bool override;

		/* Main handles */
		btDefaultCollisionConfiguration* collision_configuration_ = nullptr;
		btCollisionDispatcher* dispatcher_ = nullptr;
		btBroadphaseInterface* broadphase_interface_ = nullptr;
		btSequentialImpulseConstraintSolver* solver_ = nullptr;
		btDiscreteDynamicsWorld* dynamics_world_ = nullptr;
		btAlignedObjectArray<btCollisionShape*> collsion_shapes_ = {};
	};
}
