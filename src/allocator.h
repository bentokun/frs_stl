#pragma once

#include <cstdlib>

#include "rules.h"

#ifndef PAD_ALIGN
#define PAD_ALIGN 16
#endif

#define FORCE_INLINE __forceinline

namespace FRS {


	//Review from Godot Engine
	class memory {
	private:

		static size_t m_mem_usage, m_max_usage;
		static size_t m_alloc_count;

	public:
		memory() {
			m_mem_usage = 0;
			m_max_usage = 0;
			m_alloc_count = 0;
		};

		static void* static_alloc(size_t p_size, bool p_align = false) {
			void* t_mem = malloc(p_size + (p_align ? PAD_ALIGN : 0));

			//Manage, Add the allocted count
			m_alloc_count++;

			//Do some math to align memory
			if (p_align) {
				uint64* s = reinterpret_cast<uint64*>(t_mem);
				*s = p_size;

				uint8* s8 = reinterpret_cast<uint8*>(t_mem);

				m_mem_usage += p_size;
				if (m_mem_usage > m_max_usage) {
					m_max_usage = m_mem_usage;
				}

				return s8 + PAD_ALIGN;
			}

			return t_mem;
		};


		static void* static_realloc(void* p_mem, size_t p_size, bool p_align = false) {
			if (p_mem == nullptr) {
				return static_alloc(p_size, p_align);
			}
			
			uint8* t_mem = reinterpret_cast<uint8*>(p_mem);

			if (p_align) {
				t_mem -= PAD_ALIGN;
				uint64* s = reinterpret_cast<uint64*>(t_mem);

				m_mem_usage -= *s;
				m_mem_usage += p_size;

				if (p_size == 0) {
					free(p_mem);
					return nullptr;
				}
				else {
					*s = p_size;

					t_mem = reinterpret_cast<uint8*>(realloc(t_mem, p_size + PAD_ALIGN));
					s = reinterpret_cast<uint64*>(t_mem);

					*s = p_size;

					return t_mem + PAD_ALIGN;
				}
			}
			
			t_mem = reinterpret_cast<uint8*>(realloc(t_mem, p_size));

			return t_mem;
		};

		static void static_free(void* p_ptr, bool p_align = false) {
			uint8* t_mem = reinterpret_cast<uint8*>(p_ptr);

			m_alloc_count--;

			if (p_align) {
				t_mem -= PAD_ALIGN;

				uint64* s = reinterpret_cast<uint64*>(t_mem);

				m_mem_usage -= *s;

				try {
					free(t_mem);
				}
				catch (...) {};
			}

			try {
				free(t_mem);
			}
			catch (...) {
		
			};
			
		};

		static size_t get_mem_available() {
			return 0xFFFFFFFFFFFFF;
		};

		static size_t get_mem_usage() {
			return m_mem_usage;
		};

		static size_t get_mem_max() {
			return m_max_usage;
		};
	};

	template <typename T>
	struct default_allocator {
	public:
		static T* alloc(size_t p_memory) {
			return reinterpret_cast<T*>(memory::static_alloc(p_memory, false));
		}

		static void free(T* p_ptr) {
			return memory::static_free(reinterpret_cast<void*>(p_ptr), false);
		}
	};

	template <typename T>
	struct allocator {
		static T* alloc(size_t p_memory, bool p_pad_align = false) {
			return reinterpret_cast<T*>(memory::static_alloc(p_memory, p_pad_align));
		}

		static void free(T* p_ptr, bool p_pad_align = false) {
			return memory::static_free(reinterpret_cast<void*>(p_ptr), p_pad_align);
		}
	};
}