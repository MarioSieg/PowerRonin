#include "../Include/PowerRonin/Blob.hpp"
#include "../Include/PowerRonin/Platform.hpp"
#include "../Include/PowerRonin/Exceptions.hpp"

namespace PowerRonin
{
	void ReadBlobFromDisk(const std::filesystem::path& filePath, Blob& out)
	{
		const auto path = filePath.string();
		FILE* file;
#if COM_MSVC
		fopen_s(&file, path.c_str(), "rb");
#else
		file = fopen(path.c_str(), "rb");
#endif
		if (!file) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed: " + filePath.string());
		}
		fseek(file, 0, SEEK_END);
		const long size = ftell(file);
		if (!size) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed: " + filePath.string());
		}
		rewind(file);
		out.resize(size);
		const auto read = fread(out.data(), sizeof(std::byte), size, file);
		if (static_cast<unsigned long long>(size) != read) [[unlikely]]
		{
			throw MAKE_FATAL_ENGINE_EXCEPTION("Binary blob read failed: " + filePath.string());
		}
	}
}
