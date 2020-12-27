#pragma once

namespace dce {
	struct ScopedVectoredExceptionHandler final {
		ScopedVectoredExceptionHandler();
		ScopedVectoredExceptionHandler(const ScopedVectoredExceptionHandler&) = delete;
		ScopedVectoredExceptionHandler(ScopedVectoredExceptionHandler&&) = delete;
		auto operator=(const ScopedVectoredExceptionHandler&) = delete;
		auto operator=(ScopedVectoredExceptionHandler&&) = delete;
		~ScopedVectoredExceptionHandler();

	private:
		void* handler_ = nullptr;
	};
}
