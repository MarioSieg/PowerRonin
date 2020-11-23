// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: pyobj.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 23.11.2020 18:21

#include "pyobj.hpp"

namespace dce::scripting::py {

	CPyObject::CPyObject(PyObject* const _object) noexcept : obj_(_object) {}

	CPyObject::~CPyObject() {
		this->release();
	}

	auto CPyObject::operator->() noexcept -> PyObject* {
		return this->obj_;
	}

	auto CPyObject::operator->() const noexcept -> const PyObject* {
		return this->obj_;
	}

	CPyObject::operator bool() const noexcept {
		return this->obj_;
	}

	auto CPyObject::operator++() const -> PyObject* {
		[[likely]] if (this->obj_) {
			Py_INCREF(this->obj_);
		}
		return this->obj_;
	}

	void CPyObject::release() const {
		[[likely]] if (this->obj_) {
			Py_DECREF(this->obj_);
		}
	}
}
