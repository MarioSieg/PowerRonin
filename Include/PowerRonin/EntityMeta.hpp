#pragma once

#include <string>
#include <cstdint>

namespace PowerRonin
{
	/* Base metadata component for entities. */
	class MetaData final
	{
	public:
		std::string Name = {};
		std::string Description = {};
		void* UserData = nullptr;
		std::uint16_t Tag = 0;
		std::uint16_t Layer = 0;
	};
}
