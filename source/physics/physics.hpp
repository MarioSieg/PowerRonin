#pragma once

#include "../../Include/PowerRonin/core/Kernel.hpp"
#include "physics_headers.hpp"

namespace PowerRonin::Physics
{
	class PhysicsSystem final : public Core::ISubsystem
	{
	public:
		/* Constructors, assignment operators, destructor */
		PhysicsSystem();
		PhysicsSystem(const PhysicsSystem&) = delete;
		PhysicsSystem(PhysicsSystem&&) = delete;
		auto operator=(const PhysicsSystem&) -> PhysicsSystem& = delete;
		auto operator=(PhysicsSystem&&) -> PhysicsSystem& = delete;
		~PhysicsSystem() override = default;

	private:
		/* Required kernel events */
		static constexpr auto EVENTS = Core::ServiceEvents::PreStartup | Core::ServiceEvents::PostTick |
			Core::ServiceEvents::PreShutdown;

		/* Kernel events */
		virtual void OnPreStartup(Runtime&) override;
		virtual void OnPostTick(Runtime&) override;
		virtual void OnPreShutdown(Runtime&) override;

		/* Main handles */
		btDefaultCollisionConfiguration* collision_configuration_ = nullptr;
		btCollisionDispatcher* dispatcher_ = nullptr;
		btBroadphaseInterface* broadphase_interface_ = nullptr;
		btSequentialImpulseConstraintSolver* solver_ = nullptr;
		btDiscreteDynamicsWorld* dynamics_world_ = nullptr;
		btAlignedObjectArray<btCollisionShape*> collsion_shapes_ = {};
	};
}
