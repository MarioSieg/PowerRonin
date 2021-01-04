#pragma once

namespace std
{
	class exception;
}

namespace power_ronin
{
	class FatalEngineException;
	/// <summary>
/// (ERROR ROUTINE) Creates error dump to std::cerr and a file.
/// </summary>
	extern void create_fatal_dump();

	/// <summary>
	/// (ERROR ROUTINE) Creates error dump to std::cerr and a file.
	/// </summary>
	extern void create_fatal_dump(const std::exception& _ex);

	/// <summary>
	/// (ERROR ROUTINE) Creates error dump to std::cerr and a file.
	/// </summary>
	extern void create_fatal_dump(const FatalEngineException& _ex);
}
