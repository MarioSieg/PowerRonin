// Warning! This is an engine system file! 
// Any changes could break internal systems!
// Standard: C++20
// File: pystreamhook.cpp
// Author: Mario
// Solution: 
// Project: DreamcastSDK
// Created: 23.11.2020 21:23

#include "pystreamhook.hpp"

namespace dce::scripting::py {

	auto stdout_write(PyObject* const _self, PyObject* const _args) -> PyObject* {
		std::size_t written = 0;
		auto* const stream = reinterpret_cast<StdoutStream* const>(_self);
		[[likely]] if (stream->hook) {
			char* buf;
			[[unlikely]] if (!PyArg_ParseTuple(_args, "s", &buf)) {
				return nullptr;
			}
			std::string data = buf;
			written = data.size();
			stream->hook(std::move(data));
		}
		return PyLong_FromSize_t(written);
	}

	auto stdout_flush(PyObject* const _self, PyObject* const _args) -> PyObject* {
		return Py_BuildValue("");
	}

	static PyMethodDef STDOUT_METHODS[] = {
		{"write", &stdout_write, METH_VARARGS, "sys.stdout.write"}, {"flush", &stdout_flush, METH_VARARGS, "sys.stdout.flush"}, {nullptr, nullptr, 0, nullptr} /* Sentinel */
	};

	static PyTypeObject STDOUT_TYPE = {
		PyVarObject_HEAD_INIT(nullptr, 0) "native.StdoutStream", /* tp_name */
		sizeof(StdoutStream)
		, /* tp_basicsize */
		0
		, /* tp_itemsize */
		nullptr
		, /* tp_dealloc */
		nullptr
		, /* tp_print */
		nullptr
		, /* tp_getattr */
		nullptr
		, /* tp_setattr */
		nullptr
		, /* tp_reserved */
		nullptr
		, /* tp_repr */
		nullptr
		, /* tp_as_number */
		nullptr
		, /* tp_as_sequence */
		nullptr
		, /* tp_as_mapping */
		nullptr
		, /* tp_hash  */
		nullptr
		, /* tp_call */
		nullptr
		, /* tp_str */
		nullptr
		, /* tp_getattro */
		nullptr
		, /* tp_setattro */
		nullptr
		, /* tp_as_buffer */
		Py_TPFLAGS_DEFAULT, /* tp_flags */
		"Native stdout hook"
		, /* tp_doc */
		nullptr
		, /* tp_traverse */
		nullptr
		, /* tp_clear */
		nullptr
		, /* tp_richcompare */
		0
		, /* tp_weaklistoffset */
		nullptr
		, /* tp_iter */
		nullptr
		, /* tp_iternext */
		STDOUT_METHODS
		, /* tp_methods */
		nullptr
		, /* tp_members */
		nullptr
		, /* tp_getset */
		nullptr
		, /* tp_base */
		nullptr
		, /* tp_dict */
		nullptr
		, /* tp_descr_get */
		nullptr
		, /* tp_descr_set */
		0
		, /* tp_dictoffset */
		nullptr
		, /* tp_init */
		nullptr
		, /* tp_alloc */
		nullptr
		, /* tp_new */
	};

	static PyModuleDef EMBEDDED_MODULE = {PyModuleDef_HEAD_INIT, "native", nullptr, -1, nullptr};

	PyObject* G_STDOUT;
	PyObject* G_STDOUT_BACKUP;

	PyObject* stdout_init() {
		G_STDOUT = G_STDOUT_BACKUP = nullptr;
		STDOUT_TYPE.tp_new = &PyType_GenericNew;
		[[unlikely]] if (PyType_Ready(&STDOUT_TYPE) < 0) {
			return nullptr;
		}

		auto* const module = PyModule_Create(&EMBEDDED_MODULE);
		[[unlikely]] if (module) {
			Py_INCREF(&STDOUT_TYPE);
			PyModule_AddObject(module, "StdoutStream", reinterpret_cast<PyObject*>(&STDOUT_TYPE));
		}
		return module;
	}

	void stdout_pre_initialize() {
		PyImport_AppendInittab("native", &stdout_init);
	}

	void stdout_post_initialize() {
		PyImport_ImportModule("native");
	}

	void stdout_install_hook(const StreamHook& _hook) {
		[[unlikely]] if (!G_STDOUT) {
			G_STDOUT_BACKUP = PySys_GetObject("stdout");
			G_STDOUT = STDOUT_TYPE.tp_new(&STDOUT_TYPE, nullptr, nullptr);
		}

		auto* const impl = reinterpret_cast<StdoutStream* const>(G_STDOUT);
		impl->hook = _hook;
		PySys_SetObject("stdout", G_STDOUT);
	}

	void reset_hook() {
		[[unlikely]] if (!G_STDOUT_BACKUP) {
			PySys_SetObject("stdout", G_STDOUT_BACKUP);
		}
		Py_XDECREF(G_STDOUT);
		G_STDOUT = nullptr;
	}
}
