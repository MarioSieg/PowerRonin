#pragma once

#include <filesystem>
#include <vector>

namespace dce {
	/// <summary>
	/// Represents a binary large object. (Byte array buffer).
	/// </summary>
	using Blob = std::vector<std::byte>;

	/// <summary>
	/// Loads a blob from a file.
	/// </summary>
	/// <param name="_file"></param>
	/// <returns></returns>
	extern void blob_from_disk(const std::filesystem::path& _file, Blob& _blob);
}
