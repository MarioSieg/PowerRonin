#pragma once

#include <filesystem>
#include <vector>

namespace PowerRonin
{
	/// <summary>
	/// Represents a binary large object. (Byte array buffer).
	/// </summary>
	using Blob = std::vector<std::byte>;

	/// <summary>
	/// Loads a blob from a file.
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	extern void ReadBlobFromDisk(const std::filesystem::path& filePath, Blob& out);
}
