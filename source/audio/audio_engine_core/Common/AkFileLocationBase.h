#ifndef _AK_FILE_LOCATION_BASE_H_
#define _AK_FILE_LOCATION_BASE_H_

struct AkFileSystemFlags;

#include <AK/SoundEngine/Common/IAkStreamMgr.h>

class CAkFileLocationBase {
public:
	CAkFileLocationBase();
	virtual ~CAkFileLocationBase();

	//
	// Global path functions.
	// ------------------------------------------------------

	// Base path is prepended to all file names.
	// Audio source path is appended to base path whenever uCompanyID is AK and uCodecID specifies an audio source.
	// Bank path is appended to base path whenever uCompanyID is AK and uCodecID specifies a sound bank.
	// Language specific dir name is appended to path whenever "bIsLanguageSpecific" is true.
	auto SetBasePath(
		const AkOSChar* in_pszBasePath
	) -> AKRESULT;
	auto SetBankPath(
		const AkOSChar* in_pszBankPath
	) -> AKRESULT;
	auto SetAudioSrcPath(
		const AkOSChar* in_pszAudioSrcPath
	) -> AKRESULT;
	// Note: SetLangSpecificDirName() does not exist anymore. See release note WG-19397 (Wwise 2011.2).

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
		AkOSChar* out_pszFullFilePath // Full file path.
	) -> AKRESULT;

	// ID overload. 
	// The name of the file will be formatted as ID.ext. This is meant to be used with options
	// "Use SoundBank Names" unchecked, and/or "Copy Streamed Files" in the SoundBank Settings.
	// For more details, refer to the SoundBank Settings in Wwise Help, and to section "Identifying Banks" inside
	// "Sound Engine Integration Walkthrough > Integrate Wwise Elements into Your Game > Integrating Banks > 
	// Integration Details - Banks > General Information" of the SDK documentation.
	// Returns AK_Success if input flags are supported and the resulting path is not too long.
	// Returns AK_Fail otherwise.
	auto GetFullFilePath(
		AkFileID in_fileID, // File ID.
		AkFileSystemFlags* in_pFlags, // Special flags. 
		AkOpenMode in_eOpenMode, // File open mode (read, write, ...).
		AkOSChar* out_pszFullFilePath // Full file path.
	) -> AKRESULT;

protected:

	// Internal user paths.
	AkOSChar m_szBasePath[AK_MAX_PATH];
	AkOSChar m_szBankPath[AK_MAX_PATH];
	AkOSChar m_szAudioSrcPath[AK_MAX_PATH];

};

#endif //_AK_FILE_LOCATION_BASE_H_
