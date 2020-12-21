#include "AkFilePackage.h"

// Destroy file package and free memory.
void CAkFilePackage::Destroy() {
	// Cache memory pointer to ensure memory is free'd _after_ deleting this.
	void* pToRelease = m_pToRelease;

	// Call destructor.
	this->~CAkFilePackage();

	// Free memory.
	ClearMemory(pToRelease);
}

void CAkFilePackage::ClearMemory(
	void* in_pMemToRelease // Memory to free.
) {
	if (in_pMemToRelease) {
		AkFalign(AkMemID_FilePackage, in_pMemToRelease);
	}
}
