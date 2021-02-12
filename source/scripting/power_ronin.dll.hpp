#pragma once

#include <string_view>

namespace PowerRonin::Scripting
{
	constexpr std::string_view ASSEMBLY_NAME_ID = "PowerRonin";
	constexpr std::string_view ASSEMBLY_NAMESPACE_ID = "PowerRonin.Core";

	constexpr std::string_view CORE_CLASS_ID = "Core";

	constexpr std::string_view CORE_ON_PRE_STARTUP_ID = "OnPreStartup";
	constexpr std::string_view CORE_ON_POST_STARTUP_ID = "OnPostStartup";

	constexpr std::string_view CORE_ON_PRE_TICK_ID = "OnPreTick";
	constexpr std::string_view CORE_ON_POST_TICK_ID = "OnPostTick";

	constexpr std::string_view CORE_PRE_SHUTDOWN_ID = "OnPreShutdown";
	constexpr std::string_view CORE_POST_SHUTDOWN_ID = "OnPostShutdown";

	constexpr std::string_view COMMAND_DB_CLASS_ID = "CommandDB";
	constexpr std::string_view COMMAND_DB_CMD_ENTER_ID = "OnCommandEnter";
	constexpr std::uint8_t COMMAND_DB_CMD_ENTER_PARAMS = 1;
}
