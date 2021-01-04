#include "../include/power_ronin/blob.hpp"
#include "../include/power_ronin/env.hpp"
#include "../include/power_ronin/except.hpp"

namespace power_ronin
{
	void blob_from_disk(const std::filesystem::path& _file, Blob& _blob)
	{
		const auto path = _file.string();
		FILE* file;
#if COM_MSVC
		fopen_s(&file, path.c_str(), "rb");
#else
		file = fopen(_file.string().data(), "rb");
#endif
		if (!file) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed!");
		}
		fseek(file, 0, SEEK_END);
		const long size = ftell(file);
		if (!size) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed!");
		}
		rewind(file);
		_blob.resize(size);
		const auto read = fread(_blob.data(), sizeof(std::byte), size, file);
		if (static_cast<unsigned long long>(size) != read) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed!");
		}
	}
}
