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

#include "../../include/power_ronin/core/kernel.hpp"
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
		void OnPreStartup(Runtime&)override;
		void OnPostTick(Runtime&) override;
		void OnPreShutdown(Runtime&) override;

		/* Main handles */
		btDefaultCollisionConfiguration* collision_configuration_ = nullptr;
		btCollisionDispatcher* dispatcher_ = nullptr;
		btBroadphaseInterface* broadphase_interface_ = nullptr;
		btSequentialImpulseConstraintSolver* solver_ = nullptr;
		btDiscreteDynamicsWorld* dynamics_world_ = nullptr;
		btAlignedObjectArray<btCollisionShape*> collsion_shapes_ = {};
	};
}
