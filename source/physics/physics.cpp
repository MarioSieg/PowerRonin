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

#include "physics.hpp"

namespace dce::physics {
	Physics::Physics() : ISubsystem("Physics", EVENTS) { }

	auto Physics::on_pre_startup(Runtime&) -> bool {
		this->collision_configuration_ = new btDefaultCollisionConfiguration();
		this->dispatcher_ = new btCollisionDispatcher(this->collision_configuration_);
		this->broadphase_interface_ = new btDbvtBroadphase();
		this->solver_ = new btSequentialImpulseConstraintSolver();
		this->dynamics_world_ = new btDiscreteDynamicsWorld(this->dispatcher_, this->broadphase_interface_, this->solver_
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
