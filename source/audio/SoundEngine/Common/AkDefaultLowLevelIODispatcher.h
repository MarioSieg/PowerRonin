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
	virtual ~CAkDefaultLowLevelIODispatcher();

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
	// Default dispatcher services.
	//-----------------------------------------------------------------------------

	// Add a "device" (actually, a File Location Resolver) to the dispatcher's list. 
	// The first device added will be the first device queried.
	virtual AKRESULT AddDevice(AK::StreamMgr::IAkFileLocationResolver* in_pHook);

	// Remove all devices from the dispatcher's array.
	virtual void RemoveAllDevices();

protected:

	// List of devices.
	AK::StreamMgr::IAkFileLocationResolver* m_arDevices[AK_MAX_IO_DEVICES];
	AkUInt32 m_uNumDevices;
};

#endif //_AK_DEFAULT_LOW_LEVEL_IO_DISPATCHER_H_
