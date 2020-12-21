#ifndef _AK_FILE_PACKAGE_LOW_LEVEL_IO_DEFERRED_H_
#define _AK_FILE_PACKAGE_LOW_LEVEL_IO_DEFERRED_H_

#include "../Common/AkFilePackageLowLevelIO.h"
#include "AkDefaultIOHookDeferred.h"

class CAkFilePackageLowLevelIODeferred
	: public CAkFilePackageLowLevelIO<CAkDefaultIOHookDeferred> {
public:
	CAkFilePackageLowLevelIODeferred() = default;
	virtual ~CAkFilePackageLowLevelIODeferred() = default;

	// Override Cancel: The Windows platform SDK only permits cancellations of all transfers 
	// for a given file handle. Since the packaged files share the same handle, we cannot do this.
	void Cancel(
		AkFileDesc& in_fileDesc, // File descriptor.
		AkAsyncIOTransferInfo& io_transferInfo, // Transfer info to cancel.
		bool& io_bCancelAllTransfersForThisFile
		// Flag indicating whether all transfers should be cancelled for this file (see notes in function description).
	) override {
		if (!IsInPackage(in_fileDesc)) {
			CAkDefaultIOHookDeferred::Cancel(
				in_fileDesc, // File descriptor.
				io_transferInfo, // Transfer info to cancel.
				io_bCancelAllTransfersForThisFile
				// Flag indicating whether all transfers should be cancelled for this file (see notes in function description).
			);
		}
	}
};

#endif //_AK_FILE_PACKAGE_LOW_LEVEL_IO_DEFERRED_H_
