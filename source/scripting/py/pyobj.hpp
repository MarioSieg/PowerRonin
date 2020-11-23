// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: pyobj.hpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 23.11.2020 18:21

#pragma once

#include "python.hpp"

namespace dce::scripting::py {
	class CPyObject final {
	public:
		CPyObject() noexcept = default;
		explicit CPyObject(PyObject* const _object) noexcept;
		CPyObject(const CPyObject&) = delete;
		CPyObject(CPyObject&&) = delete;
		auto operator=(const CPyObject&) -> CPyObject& = delete;
		auto operator=(CPyObject&&) -> CPyObject& = delete;

		/// <summary>
		/// Release
		/// </summary>
		~CPyObject();

		/// <summary>
		/// Access underlying py object.
		/// </summary>
		/// <returns>Py object ptr</returns>
		auto operator->() noexcept -> PyObject*;

		/// <summary>
		/// Access underlying py object.
		/// </summary>
		/// <returns>Py object ptr</returns>
		auto operator->() const noexcept -> const PyObject*;

		/// <summary>
		/// Check if underlying py object pointer is valid.
		/// </summary>
		/// <returns>True if valid, else false.</returns>
		operator bool() const noexcept;

		/// <summary>
		/// Add reference to reference count.
		/// </summary>
		/// <returns></returns>
		auto operator++() const -> PyObject*;

		/// <summary>
		/// Release memory.
		/// </summary>
		void release() const;

	private:
		PyObject* obj_ = nullptr;
	};
}
