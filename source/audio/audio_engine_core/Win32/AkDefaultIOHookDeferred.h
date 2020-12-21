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
class CAkDefaultIOHookDeferred : public AK::StreamMgr::IAkFileLocationResolver
                                 , public AK::StreamMgr::IAkIOHookDeferred
                                 , public CAkMultipleFileLocation {
public:

	CAkDefaultIOHookDeferred();
	~CAkDefaultIOHookDeferred() override;

	// Initialization/termination. Init() registers this object as the one and 
	// only File Location Resolver if none were registered before. Then 
	// it creates a streaming device with scheduler type AK_SCHEDULER_DEFERRED_LINED_UP.
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
	// IAkIOHookDeferred interface.
	//-----------------------------------------------------------------------------

	// Reads data from a file (asynchronous).
	auto Read(
		AkFileDesc& in_fileDesc, // File descriptor.
		const AkIoHeuristics& in_heuristics, // Heuristics for this data transfer.
		AkAsyncIOTransferInfo& io_transferInfo // Asynchronous data transfer info.
	) override
	->
	AKRESULT override;

	// Writes data to a file (asynchronous).
	auto Write(
		AkFileDesc& in_fileDesc, // File descriptor.
		const AkIoHeuristics& in_heuristics, // Heuristics for this data transfer.
		AkAsyncIOTransferInfo& io_transferInfo // Platform-specific asynchronous IO operation info.
	) override
	->
	AKRESULT override;

	// Notifies that a transfer request is cancelled. It will be flushed by the streaming device when completed.
	void Cancel(
		AkFileDesc& in_fileDesc, // File descriptor.
		AkAsyncIOTransferInfo& io_transferInfo, // Transfer info to cancel.
		bool& io_bCancelAllTransfersForThisFile
		// Flag indicating whether all transfers should be cancelled for this file (see notes in function description).
	) override override;

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
		AkDeviceDesc& out_deviceDesc // Description of associated low-level I/O device.
	) override override;

	// Returns custom profiling data: 1 if file opens are asynchronous, 0 otherwise.
	auto GetDeviceData() override
	->
	AkUInt32 override;

protected:

	// Local callback for overlapped I/O.
	static VOID CALLBACK FileIOCompletionRoutine(
		DWORD dwErrorCode,
		DWORD dwNumberOfBytesTransfered,
		LPOVERLAPPED lpOverlapped
	);

protected:

	AkDeviceID m_deviceID;
	bool m_bAsyncOpen{false}; // If true, opens files asynchronously when it can.

	// Structures for concurrent asynchronous transfers bookkeeping.
	// Note 1: The pool is a fixed block size pool. It returns OVERLAPPED objects. Allocation is guaranteed
	// because the pool size is MaxConcurrentIO * sizeof(OVERLAPPED).
	// Note 2: accesses to memory pool are not locked, because we only use the platform SDK here,
	// which is executed by the I/O thread when it is in an alertable state.
	// If you release overlapped objects from your own thread, a lock is mandatory.
	// Note 3: we use the hEvent field to store a pointer to the AkAsyncIOTransferInfo structure.

	// Get a free slot for an OVERLAPPED I/O transfer.
	auto GetFreeOverlapped(
		AkAsyncIOTransferInfo* in_pTransfer
		// Transfer that will use this OVERLAPPED. Its address is stored in OVERLAPPED::hEvent.
	) -> OVERLAPPED* {
		auto* pOverlapped = static_cast<OVERLAPPED*>(AK::MemoryMgr::Malloc(AkMemID_Streaming, sizeof OVERLAPPED));
		AKASSERT(pOverlapped || !"Too many concurrent transfers in the Low-Level IO");
		pOverlapped->hEvent = in_pTransfer;
		return pOverlapped;
	}

	// Release a slot after an OVERLAPPED I/O transfer.
	static inline void ReleaseOverlapped(
		OVERLAPPED* in_pOverlapped // OVERLAPPED structure to release. 
	) {
		AK::MemoryMgr::Free(AkMemID_Streaming, in_pOverlapped);
	}
};

#endif //_AK_DEFAULT_IO_HOOK_DEFERRED_H_
