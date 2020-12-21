#ifndef _AK_DEFAULT_IO_HOOK_BLOCKING_H_
#define _AK_DEFAULT_IO_HOOK_BLOCKING_H_

#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include "../Common/AkMultipleFileLocation.h"

//-----------------------------------------------------------------------------
// Name: class CAkDefaultIOHookBlocking.
// Desc: Implements IAkIOHookBlocking low-level I/O hook, and 
//		 IAkFileLocationResolver. Can be used as a standalone Low-Level I/O
//		 system, or as part of a system with multiple devices.
//		 File location is resolved using simple path concatenation logic.
//-----------------------------------------------------------------------------
class CAkDefaultIOHookBlocking : public AK::StreamMgr::IAkFileLocationResolver
                                 , public AK::StreamMgr::IAkIOHookBlocking
                                 , public CAkMultipleFileLocation {
public:

	CAkDefaultIOHookBlocking();
	~CAkDefaultIOHookBlocking() override;

	// Initialization/termination. Init() registers this object as the one and 
	// only File Location Resolver if none were registered before. Then 
	// it creates a streaming device with scheduler type AK_SCHEDULER_BLOCKING.
	auto Init(
		const AkDeviceSettings& in_deviceSettings, // Device settings.
		bool in_bAsyncOpen = AK_ASYNC_OPEN_DEFAULT // If true, files are opened asynchronously when possible.
	) -> AKRESULT;
	void Term();


	//
	// IAkFileLocationAware interface.
	//-----------------------------------------------------------------------------

	// Returns a file descriptor for a given file name (string).
	auto Open(
		const AkOSChar* in_pszFileName, // File name.
		AkOpenMode in_eOpenMode, // Open mode.
		AkFileSystemFlags* in_pFlags, // Special flags. Can pass NULL.
		bool& io_bSyncOpen,
		// If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
		AkFileDesc& out_fileDesc // Returned file descriptor.
	) override
	->
	AKRESULT override;

	// Returns a file descriptor for a given file ID.
	auto Open(
		AkFileID in_fileID, // File ID.
		AkOpenMode in_eOpenMode, // Open mode.
		AkFileSystemFlags* in_pFlags, // Special flags. Can pass NULL.
		bool& io_bSyncOpen,
		// If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
		AkFileDesc& out_fileDesc // Returned file descriptor.
	) override
	->
	AKRESULT override;


	//
	// IAkIOHookBlocking interface.
	//-----------------------------------------------------------------------------

	// Reads data from a file (synchronous). 
	auto Read(
		AkFileDesc& in_fileDesc, // File descriptor.
		const AkIoHeuristics& in_heuristics, // Heuristics for this data transfer.
		void* out_pBuffer, // Buffer to be filled with data.
		AkIOTransferInfo& io_transferInfo // Synchronous data transfer info. 
	) override
	->
	AKRESULT override;

	// Writes data to a file (synchronous). 
	auto Write(
		AkFileDesc& in_fileDesc, // File descriptor.
		const AkIoHeuristics& in_heuristics, // Heuristics for this data transfer.
		void* in_pData, // Data to be written.
		AkIOTransferInfo& io_transferInfo // Synchronous data transfer info. 
	) override
	->
	AKRESULT override;

	// Cleans up a file.
	auto Close(
		AkFileDesc& in_fileDesc // File descriptor.
	) override
	->
	AKRESULT override;

	// Returns the block size for the file or its storage device. 
	auto GetBlockSize(
		AkFileDesc& in_fileDesc // File descriptor.
	) override
	->
	AkUInt32 override;

	// Returns a description for the streaming device above this low-level hook.
	void GetDeviceDesc(
		AkDeviceDesc& out_deviceDesc // Device description.
	) override override;

	// Returns custom profiling data: 1 if file opens are asynchronous, 0 otherwise.
	auto GetDeviceData() override
	->
	AkUInt32 override;

protected:
	AkDeviceID m_deviceID;
	bool m_bAsyncOpen{false}; // If true, opens files asynchronously when it can.
};

#endif //_AK_DEFAULT_IO_HOOK_BLOCKING_H_
