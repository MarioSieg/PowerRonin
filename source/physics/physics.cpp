#include "physics.hpp"

namespace dce::physics {
	Physics::Physics() : ISubsystem("Physics", EVENTS) {
	}

	auto Physics::on_pre_startup(Runtime&) -> bool {
		this->collision_configuration_ = new btDefaultCollisionConfiguration();
		this->dispatcher_ = new btCollisionDispatcher(this->collision_configuration_);
		this->broadphase_interface_ = new btDbvtBroadphase();
		this->solver_ = new btSequentialImpulseConstraintSolver();
		this->dynamics_world_ = new btDiscreteDynamicsWorld(this->dispatcher_, this->broadphase_interface_,
		                                                    this->solver_
		                                                    , this->collision_configuration_);
		this->dynamics_world_->setGravity({.0f, -10.f, .0f});
		return true;
	}

	auto Physics::on_post_tick(Runtime& _rt) -> bool {
		/* TODO
		_rt.scenery().registry().view<Transform, Rigidbody, Collider>().each([ ](Transform &_transform, Rigidbody &_rigidbody, Collider &_collider) {
	  
		});
		*/
		return true;
	}

	auto Physics::on_pre_shutdown(Runtime&) -> bool {
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

		return true;
	}
}
