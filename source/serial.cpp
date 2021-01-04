#include "../include/power_ronin/serial.hpp"
#include "../include/power_ronin/json_impl.hpp"
#include <fstream>

namespace power_ronin
{
	auto ISerializable::serialize_to_file(const std::filesystem::path& _path) const -> bool
	{
		std::ofstream file(_path);
		if (!file)
		{
			return false;
		}
		JsonStream stream{};
		this->serialize(stream);
		file << std::setw(4) << stream;
		return true;
	}

	auto ISerializable::deserialize_from_file(const std::filesystem::path& _path) -> bool
	{
		std::ifstream file(_path);
		if (!file)
		{
			return false;
		}
		JsonStream stream;
		file >> stream;
		if (!stream)
		{
			return false;
		}
		this->deserialize(stream);
		return true;
	}
} // namespace power_ronin // namespace power_ronin
