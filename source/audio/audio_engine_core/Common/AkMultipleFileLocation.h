#ifndef _AK_MULTI_FILE_LOCATION_H_
#define _AK_MULTI_FILE_LOCATION_H_

struct AkFileSystemFlags;

#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/Tools/Common/AkListBareLight.h>


// This file location class supports multiple base paths for Wwise file access.
// Each path will be searched the reverse order of the addition order until the file is found.
class CAkMultipleFileLocation {
protected:

	// Internal user paths.
	struct FilePath {
		FilePath* pNextLightItem;
		AkOSChar szPath[1]; //Variable length
	};

public:
	void Term();

	//
	// Global path functions.
	// ------------------------------------------------------

	// Base path is prepended to all file names.
	// Audio source path is appended to base path whenever uCompanyID is AK and uCodecID specifies an audio source.
	// Bank path is appended to base path whenever uCompanyID is AK and uCodecID specifies a sound bank.
	// Language specific dir name is appended to path whenever "bIsLanguageSpecific" is true.
	auto SetBasePath(const AkOSChar* in_pszBasePath) -> AKRESULT {
		return AddBasePath(in_pszBasePath);
	}

	auto AddBasePath(const AkOSChar* in_pszBasePath) -> AKRESULT;

	auto Open(
		const AkOSChar* in_pszFileName, // File name.
		AkOpenMode in_eOpenMode, // Open mode.
		AkFileSystemFlags* in_pFlags, // Special flags. Can pass NULL.
		bool in_bOverlapped, // Overlapped IO open
		AkFileDesc& out_fileDesc // Returned file descriptor.
	) -> AKRESULT;


	auto Open(
		AkFileID in_fileID, // File ID.
		AkOpenMode in_eOpenMode, // Open mode.
		AkFileSystemFlags* in_pFlags, // Special flags. Can pass NULL.
		bool in_bOverlapped, // Overlapped IO open
		AkFileDesc& out_fileDesc // Returned file descriptor.
	) -> AKRESULT;

	//
	// Path resolving services.
	// ------------------------------------------------------

	// String overload.
	// Returns AK_Success if input flags are supported and the resulting path is not too long.
	// Returns AK_Fail otherwise.
	auto GetFullFilePath(
		const AkOSChar* in_pszFileName, // File name.
		AkFileSystemFlags* in_pFlags, // Special flags. Can be NULL.
		AkOpenMode in_eOpenMode, // File open mode (read, write, ...).
		AkOSChar* out_pszFullFilePath, // Full file path.
		AkOSChar* in_pszBasePath = nullptr // Base path to use.  If null, the first suitable location will be given.		
	) -> AKRESULT;

protected:

	AkListBareLight<FilePath> m_Locations;
};

namespace AkMultipleFileLocation {
	void ConvertFileIdToFilename(AkOSChar* out_pszTitle, AkUInt32 in_pszTitleMaxLen, AkUInt32 in_codecId,
	                             AkFileID in_fileID);
}
#endif //_AK_MULTI_FILE_LOCATION_H_
