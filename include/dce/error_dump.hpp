#pragma once

namespace std
{
	class exception;
}

namespace dce
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
