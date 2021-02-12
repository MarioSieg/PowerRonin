#include "physics.hpp"

namespace PowerRonin::Physics
{
	PhysicsSystem::PhysicsSystem() : ISubsystem("Physics", EVENTS) { }

	void PhysicsSystem::OnPreStartup(Runtime&)
	{
		this->collision_configuration_ = new btDefaultCollisionConfiguration();
		this->dispatcher_ = new btCollisionDispatcher(this->collision_configuration_);
		this->broadphase_interface_ = new btDbvtBroadphase();
		this->solver_ = new btSequentialImpulseConstraintSolver();
		this->dynamics_world_ = new btDiscreteDynamicsWorld(this->dispatcher_, this->broadphase_interface_,
		                                                    this->solver_
		                                                    , this->collision_configuration_);
		this->dynamics_world_->setGravity({.0f, -10.f, .0f});
	}

	void PhysicsSystem::OnPostTick(Runtime&) { }

	void PhysicsSystem::OnPreShutdown(Runtime&)
	{
		delete this->dynamics_world_;
		this->dynamics_world_ = nullptr;

		delete this->solver_;
		this->solver_ = nullptr;

		delete this->broadphase_interface_;
		this->broadphase_interface_ = nullptr;

		delete this->dispatcher_;
		this->dispatcher_ = nullptr;

		delete this->collision_configuration_;
		this->collision_configuration_ = nullptr;
	}
}
