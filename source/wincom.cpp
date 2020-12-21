#include "wincom.hpp"

// We cannot use #if SYS_WINDOWS
// because one of the fucking headers defines some enumerators with that name.
#if _WIN64
#include <combaseapi.h>
#endif

namespace dce {

	void co_initialize() {
#if  _WIN64
		CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
#endif
	}

	void co_uninitialize() {
#if  _WIN64
		CoUninitialize();
#endif
	}
}
