#pragma once

#include "Rules.h"

#include <nmmintrin.h>

namespace FRS {

	/*
		@ Function    : mem_copy
		@ Description : copy the memory from the source pointer
						to destination pointer, with size

		@ Date        : 05/28/2017 | 6:28 PM
		@ Method      : Using C++ template, the copy time will
						always improve, 'cause the type is known
	*/
	template <typename T1, typename T2>
	void mem_copy(T1 dest, T2 src, size64 size) {

		if (src == dest || size == 0)
			return;

		size64 loops = (size / sizeof(*src));
		size64 destSize = sizeof(*dest);

		auto m_dest = dest;
		auto m_src = src;

		for (size64 i = 0; i < loops; i++) {
			*m_dest++ = *m_src++;
		}
	}

	template <typename T>
	void fill(T* dest, T data, uint32 num_element) {
		for (uint64 i = 0; i < num_element; i++) {
			*dest++ = data;
		}
	};

	/*
		@ Function    : mem_copy
		@ Description : copy the memory from the source pointer
		to destination pointer, with size
		@ Date        : 05/28/2017 | 1:25 PM
		@ Method      : Copying 4 bytes is always faster than copying 1 bytes each time.
		The method here is first copying 4 bytes/ time for size / 4 times.
		The remaining bytes is copy with speed of 1 bytes/ time
	*/
	void mem_copy_c(void* dest, void* src, size64 size) {

		if (src == dest || size == 0)
			return;

		uint8* pDes = static_cast<uint8*>(dest);
		uint8* pSrc = static_cast<uint8*>(src);

		size64 loops = (size / sizeof(uint32));

		for (size64 index = 0; index < loops; ++index) {
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

	/*
		@ Function    : mem_copy
		@ Description : copy the memory from the source pointer
		to destination pointer, with size
		@ Date        : 05/28/2017 | 8:23 PM
		@ Method      : Copying 4 bytes is always faster than copying 1 bytes each time.
		The method here is first copying 4 bytes/ time for size / 4 times.
		The remaining bytes is copy with speed of 1 bytes/ time. The 4 bytes part
		is done using SSE2 intricts
	*/
	void mem_copy_sse(void* dest, void* src, size64 size) {

		if (src == dest || size == 0)
			return;

		size64 loops = (size / sizeof(float));

		float* m_dest = static_cast<float*>(dest);
		float* m_src = static_cast<float*>(src);

		for (size64 i = 0; i < loops; i++) {
			__m128 buffer = _mm_load_ps(m_src);
			_mm_store_ps(m_dest, buffer);

			m_src  += sizeof(float);
			m_dest += sizeof(float);
		}

		loops = size % sizeof(float);

		for (uint32 index = 0; index < loops; ++index) {
			*m_dest = *m_src;
			++m_dest;
			++m_src;
		}

	}

	/*
		@ Function    : mem_move
		@ Description : move the memory from the source pointer
		to destination pointer, with size
		@ Date        : 05/28/2017 | 8:49 PM
		@ Method      : not now this is ugly.
						Basiclly, we just check the situation
						of the src and dst pointer, if it overlaps
						than we copy memory in a ugly way
	*/
	void mem_move_c(void* dest, void* src, size64 size) {
		uint8* pDes = static_cast<uint8*>(dest);
		uint8* pSrc = static_cast<uint8*>(src);

		if (pDes == pSrc || size == 0)
			return;

		if (pDes > pSrc && pDes - pSrc < size) {

			for (size64 i = size - 1; i >= 0; i--) {
				pDes[i] = pSrc[i];
			}

			return;
		}

		if (pDes < pSrc && pSrc - pDes < size) {
			for (size64 i = 0; i < size; i++)
				pDes[i] = pSrc[i];

			return;
		}
		
		mem_copy_c(dest, src, size);
	}
}