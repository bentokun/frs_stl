#pragma once

#include "rules.h"
#include "memory.h"
#include "swap.h"
#include "container_base.h"

namespace FRS {
	
	template <typename T>
	class container: public container_base<T>  {
	public:
		container() : container_base<T>() {};
		container(container& p_container) : container_base<T>(p_container) {};
		container(uint32 p_size, T p_data) : container_base<T>(p_size, p_data) {};
	
		T operator [](uint32 p_pos) {
			return m_array[p_pos];
		}
	};

}