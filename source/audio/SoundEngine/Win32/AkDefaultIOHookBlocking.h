// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

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
class CAkDefaultIOHookBlocking : public AK::StreamMgr::IAkFileLocationResolver, public AK::StreamMgr::IAkIOHookBlocking, public CAkMultipleFileLocation {
public:

	CAkDefaultIOHookBlocking();
	virtual ~CAkDefaultIOHookBlocking();

	// Initialization/termination. Init() registers this object as the one and 
	// only File Location Resolver if none were registered before. Then 
	// it creates a streaming device with scheduler type AK_SCHEDULER_BLOCKING.
	AKRESULT Init(const AkDeviceSettings& in_deviceSettings,
	              // Device settings.
	              bool in_bAsyncOpen = AK_ASYNC_OPEN_DEFAULT // If true, files are opened asynchronously when possible.
	);
	void Term();


	//
	// IAkFileLocationAware interface.
	//-----------------------------------------------------------------------------

	// Returns a file descriptor for a given file name (string).
	virtual AKRESULT Open(const AkOSChar* in_pszFileName,
	                      // File name.
	                      AkOpenMode in_eOpenMode,
	                      // Open mode.
	                      AkFileSystemFlags* in_pFlags,
	                      // Special flags. Can pass NULL.
	                      bool& io_bSyncOpen,
	                      // If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
	                      AkFileDesc& out_fileDesc // Returned file descriptor.
	) override;

	// Returns a file descriptor for a given file ID.
	virtual AKRESULT Open(AkFileID in_fileID,
	                      // File ID.
	                      AkOpenMode in_eOpenMode,
	                      // Open mode.
	                      AkFileSystemFlags* in_pFlags,
	                      // Special flags. Can pass NULL.
	                      bool& io_bSyncOpen,
	                      // If true, the file must be opened synchronously. Otherwise it is left at the File Location Resolver's discretion. Return false if Open needs to be deferred.
	                      AkFileDesc& out_fileDesc // Returned file descriptor.
	) override;


	//
	// IAkIOHookBlocking interface.
	//-----------------------------------------------------------------------------

	// Reads data from a file (synchronous). 
	virtual AKRESULT Read(AkFileDesc& in_fileDesc,
	                      // File descriptor.
	                      const AkIoHeuristics& in_heuristics,
	                      // Heuristics for this data transfer.
	                      void* out_pBuffer,
	                      // Buffer to be filled with data.
	                      AkIOTransferInfo& io_transferInfo // Synchronous data transfer info. 
	) override;

	// Writes data to a file (synchronous). 
	virtual AKRESULT Write(AkFileDesc& in_fileDesc,
	                       // File descriptor.
	                       const AkIoHeuristics& in_heuristics,
	                       // Heuristics for this data transfer.
	                       void* in_pData,
	                       // Data to be written.
	                       AkIOTransferInfo& io_transferInfo // Synchronous data transfer info. 
	) override;

	// Cleans up a file.
	virtual AKRESULT Close(AkFileDesc& in_fileDesc // File descriptor.
	) override;

	// Returns the block size for the file or its storage device. 
	virtual AkUInt32 GetBlockSize(AkFileDesc& in_fileDesc // File descriptor.
	) override;

	// Returns a description for the streaming device above this low-level hook.
	virtual void GetDeviceDesc(AkDeviceDesc& out_deviceDesc // Device description.
	) override;

	// Returns custom profiling data: 1 if file opens are asynchronous, 0 otherwise.
	virtual AkUInt32 GetDeviceData() override;

protected:
	AkDeviceID m_deviceID;
	bool m_bAsyncOpen; // If true, opens files asynchronously when it can.
};

#endif //_AK_DEFAULT_IO_HOOK_BLOCKING_H_
