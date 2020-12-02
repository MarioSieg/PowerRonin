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

void CAkFilePackage::ClearMemory(void* in_pMemToRelease // Memory to free.
) {
	if (in_pMemToRelease) {
		AkFalign(AkMemID_FilePackage, in_pMemToRelease);
	}
}
