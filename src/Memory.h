#pragma once

#include "Rules.h"

namespace FRS {

	/*
		@ Function    : mem_copy
		@ Description : copy the memory from the source pointer
						to destination pointer, with size

		@ Date        : 05/28/2017 | 1:25 PM
		@ Method      : Copying 4 bytes is always faster than copying 1 bytes each time.
						The method here is first copying 4 bytes/ time for size / 4 times. 
						The remaining bytes is copy with speed of 1 bytes/ time
	*/
	void mem_copy(void* dest, void* src, uint32 size) {

		uint8* pDes = static_cast<uint8*>(dest);
		uint8* pSrc = static_cast<uint8*>(src);

		uint32 loops = (size / sizeof(uint32));

		for (uint32 index = 0; index < loops; ++index) {
			*(reinterpret_cast<uint32*>(pDes)) = *(reinterpret_cast<uint32*>(pSrc));
			pDes += sizeof(uint32);
			pSrc += sizeof(uint32);
		}

		loops = size % sizeof(uint32);

		for (uint32 index = 0; index < loops; ++index) {
			*pDes = *pSrc;
			++pDes;
			++pSrc;
		}

	}

}