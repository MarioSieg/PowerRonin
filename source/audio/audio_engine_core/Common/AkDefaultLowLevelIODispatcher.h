#ifndef _AK_DEFAULT_LOW_LEVEL_IO_DISPATCHER_H_
#define _AK_DEFAULT_LOW_LEVEL_IO_DISPATCHER_H_

#include <AK/SoundEngine/Common/AkStreamMgrModule.h>

#define AK_MAX_IO_DEVICES	(3)

//-----------------------------------------------------------------------------
// Name: class CAkDefaultLowLevelIODispatcher.
// Desc: Register this object to the Stream Manager as the File Location Resolver.
//		 You need to implement dispatching calls to Open() to separate devices,
//		 according to your specific requirements.
//-----------------------------------------------------------------------------
class CAkDefaultLowLevelIODispatcher : public AK::StreamMgr::IAkFileLocationResolver {
public:

	CAkDefaultLowLevelIODispatcher();
	~CAkDefaultLowLevelIODispatcher() override;

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
	// Default dispatcher services.
	//-----------------------------------------------------------------------------

	// Add a "device" (actually, a File Location Resolver) to the dispatcher's list. 
	// The first device added will be the first device queried.
	virtual auto AddDevice(
		AK::StreamMgr::IAkFileLocationResolver* in_pHook
	) -> AKRESULT;

	// Remove all devices from the dispatcher's array.
	virtual void RemoveAllDevices();

protected:

	// List of devices.
	AK::StreamMgr::IAkFileLocationResolver* m_arDevices[AK_MAX_IO_DEVICES];
	AkUInt32 m_uNumDevices{0};
};

#endif //_AK_DEFAULT_LOW_LEVEL_IO_DISPATCHER_H_
