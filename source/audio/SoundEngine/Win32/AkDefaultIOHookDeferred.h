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

#ifndef _AK_DEFAULT_IO_HOOK_DEFERRED_H_
#define _AK_DEFAULT_IO_HOOK_DEFERRED_H_

#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include "../Common/AkMultipleFileLocation.h"
#include <AK/Tools/Common/AkAssert.h>

//-----------------------------------------------------------------------------
// Name: class CAkDefaultIOHookDeferred.
// Desc: Implements IAkIOHookDeferred low-level I/O hook, and 
//		 IAkFileLocationResolver. Can be used as a standalone Low-Level I/O
//		 system, or as part of a system with multiple devices.
//		 File location is resolved using simple path concatenation logic.
//-----------------------------------------------------------------------------
class CAkDefaultIOHookDeferred : public AK::StreamMgr::IAkFileLocationResolver, public AK::StreamMgr::IAkIOHookDeferred, public CAkMultipleFileLocation {
public:

	CAkDefaultIOHookDeferred();
	virtual ~CAkDefaultIOHookDeferred();

	// Initialization/termination. Init() registers this object as the one and 
	// only File Location Resolver if none were registered before. Then 
	// it creates a streaming device with scheduler type AK_SCHEDULER_DEFERRED_LINED_UP.
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
	);

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
	);


	//
	// IAkIOHookDeferred interface.
	//-----------------------------------------------------------------------------

	// Reads data from a file (asynchronous).
	virtual AKRESULT Read(AkFileDesc& in_fileDesc,
	                      // File descriptor.
	                      const AkIoHeuristics& in_heuristics,
	                      // Heuristics for this data transfer.
	                      AkAsyncIOTransferInfo& io_transferInfo // Asynchronous data transfer info.
	);

	// Writes data to a file (asynchronous).
	virtual AKRESULT Write(AkFileDesc& in_fileDesc,
	                       // File descriptor.
	                       const AkIoHeuristics& in_heuristics,
	                       // Heuristics for this data transfer.
	                       AkAsyncIOTransferInfo& io_transferInfo // Platform-specific asynchronous IO operation info.
	);

	// Notifies that a transfer request is cancelled. It will be flushed by the streaming device when completed.
	virtual void Cancel(AkFileDesc& in_fileDesc,
	                    // File descriptor.
	                    AkAsyncIOTransferInfo& io_transferInfo,
	                    // Transfer info to cancel.
	                    bool& io_bCancelAllTransfersForThisFile // Flag indicating whether all transfers should be cancelled for this file (see notes in function description).
	);

	// Cleans up a file.
	virtual AKRESULT Close(AkFileDesc& in_fileDesc // File descriptor.
	);

	// Returns the block size for the file or its storage device. 
	virtual AkUInt32 GetBlockSize(AkFileDesc& in_fileDesc // File descriptor.
	);

	// Returns a description for the streaming device above this low-level hook.
	virtual void GetDeviceDesc(AkDeviceDesc& out_deviceDesc // Description of associated low-level I/O device.
	);

	// Returns custom profiling data: 1 if file opens are asynchronous, 0 otherwise.
	virtual AkUInt32 GetDeviceData();

protected:

	// Local callback for overlapped I/O.
	static VOID CALLBACK FileIOCompletionRoutine(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped);

protected:

	AkDeviceID m_deviceID;
	bool m_bAsyncOpen; // If true, opens files asynchronously when it can.

	// Structures for concurrent asynchronous transfers bookkeeping.
	// Note 1: The pool is a fixed block size pool. It returns OVERLAPPED objects. Allocation is guaranteed
	// because the pool size is MaxConcurrentIO * sizeof(OVERLAPPED).
	// Note 2: accesses to memory pool are not locked, because we only use the platform SDK here,
	// which is executed by the I/O thread when it is in an alertable state.
	// If you release overlapped objects from your own thread, a lock is mandatory.
	// Note 3: we use the hEvent field to store a pointer to the AkAsyncIOTransferInfo structure.

	// Get a free slot for an OVERLAPPED I/O transfer.
	OVERLAPPED* GetFreeOverlapped(AkAsyncIOTransferInfo* in_pTransfer // Transfer that will use this OVERLAPPED. Its address is stored in OVERLAPPED::hEvent.
	) {
		OVERLAPPED* pOverlapped = (OVERLAPPED*)AK::MemoryMgr::Malloc(AkMemID_Streaming, sizeof(OVERLAPPED));
		AKASSERT(pOverlapped || !"Too many concurrent transfers in the Low-Level IO");
		pOverlapped->hEvent = in_pTransfer;
		return pOverlapped;
	}

	// Release a slot after an OVERLAPPED I/O transfer.
	static inline void ReleaseOverlapped(OVERLAPPED* in_pOverlapped // OVERLAPPED structure to release. 
	) {
		AK::MemoryMgr::Free(AkMemID_Streaming, in_pOverlapped);
	}
};

#endif //_AK_DEFAULT_IO_HOOK_DEFERRED_H_
