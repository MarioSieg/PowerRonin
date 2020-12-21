#ifndef _AK_FILE_PACKAGE_LOW_LEVEL_IO_BLOCKING_H_
#define _AK_FILE_PACKAGE_LOW_LEVEL_IO_BLOCKING_H_

#include "../Common/AkFilePackageLowLevelIO.h"
#include "AkDefaultIOHookBlocking.h"

class CAkFilePackageLowLevelIOBlocking
	: public CAkFilePackageLowLevelIO<CAkDefaultIOHookBlocking> {
public:
	CAkFilePackageLowLevelIOBlocking() = default;
	virtual ~CAkFilePackageLowLevelIOBlocking() = default;
};

#endif //_AK_FILE_PACKAGE_LOW_LEVEL_IO_BLOCKING_H_
