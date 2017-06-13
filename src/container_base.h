#pragma once
#pragma once

#include "rules.h"
#include "allocator.h"
#include "memory.h"
#include "swap.h"

namespace FRS {

	/*
	@ Class       : container_base<T>
	@ Description : template class managing an array of
	typename T
	@ Date        : 05/27/2017 | 8:34 AM
	@ Method      : Using new and delete to implement class.
	*/
	template <typename T, typename Allocator = default_allocator<T>>
	class container_base {
	protected:

		T* m_array;
		uint32 m_count;
		uint32 m_capacity;

	public:

		typedef T* Iterator;
		typedef T* Reserve_Iterator;

		/*
		@ Method      : begin
		@ Description : Get the begin iterator of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		Iterator begin() {
			return m_array;
		}

		/*
		@ Method      : end
		@ Description : Get the end iterator of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		Iterator end() {
			return m_array + m_count;
		}

		Reserve_Iterator rbegin() {
			return m_array + m_count;
		}

		Reserve_Iterator rend() {
			return m_array;
		}

		/*
		@ Method      : front
		@ Description : Get the front element of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		T front() {
			return m_array[0];
		}

		/*
		@ Method      : back
		@ Description : Get the back element of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		T back() {
			return m_array[m_count - 1];
		}


		container_base(uint32 p_num, T p_data) {
			m_count = p_num;
			m_capacity = p_num;

			m_array = Allocator::alloc(m_capacity * sizeof(T));

			memset(m_array, 0, m_capacity * sizeof(T));

			for (int32 i = 0; i < p_num; i++) {
				m_array[i] = p_data;
			}
		}

		container_base() {
			m_array = nullptr;
			m_count = 0;
			m_capacity = 0;
		}

		container_base(container_base& p_vec) {
			m_count = p_vec.m_count;
			m_capacity = p_vec.m_capacity;

			m_array = Allocator::alloc(m_capacity * sizeof(T));

			memset(m_array, 0, m_capacity * sizeof(T));

			mem_copy(m_array, p_vec.m_array, m_count * sizeof(T));
		}

		~container_base() {
			Allocator::free(m_array);
		}

		/*
		@ Method      : data
		@ Description : Get the data of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		T* data() {
			return m_array;
		}

		/*
		@ Method      : count
		@ Description : Get the size of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		uint32 count() {
			return m_count;
		}

		/*
		@ Method      : capacity
		@ Description : Get the capacity of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		uint32 capacity() {
			return m_capacity;
		}

		/*
		@ Method      : push_back
		@ Description : add a variable to the back of the array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : ----------------------------------
		Implement push_back is not hard, the core is
		set the current size-1 variable in the array
		by the parameter, if the size of arrays is
		equal or bigger than the capacity, we reserve
		it by the size plus 5.
		*/
		virtual void push_back(T p_data) {
			if ((m_count >= m_capacity)) {
				reserve(m_capacity + 5);
			}

			m_array[m_count++] = p_data;
		};

		/*
		@ Method      : pop_back
		@ Description : delete the variable at the back of the array
		@ Date        : 05/27/2017 | 8:05 AM
		@ Method      : -------------------------------------
		Pop_back is easier. Just subtract the size by one.
		*/
		virtual void pop_back() {
			m_count--;
		};

		/*
		@ Method      : reserve
		@ Description : change the capacity of the
		array by reserving bits
		@ Date        : 05/27/2017 | 8:24 AM
		@ Method      : -------------------------------
		To change capacity, we create a new array,
		copy the old array to new array and replace
		it. Pretty much like swapping.
		*/
		void reserve(uint32 p_new_capacity) {
			if (m_array == nullptr) {
				m_count = 0;
				m_capacity = 0;
			}

			T*     newArray = Allocator::alloc(p_new_capacity * sizeof(T));
			uint32 newSize = p_new_capacity < m_count ? p_new_capacity : m_count;
		
			memset(newArray, 0, p_new_capacity * sizeof(T));

			if (m_count != 0)
				mem_copy(newArray, m_array, m_count * sizeof(T));

			m_capacity = p_new_capacity;
			Allocator::free(m_array);

			m_array = Allocator::alloc(p_new_capacity * sizeof(T));
			m_array = newArray;
		};

		/*
		@ Method      : resize
		@ Description : change the size of array
		@ Date        : 05/27/2017 | 8:26 AM
		@ Method      : -------------------
		Change the capacity of the
		array by p_num, than set the size
		by p_num
		*/
		void resize(int32 p_num) {
			reserve(p_num);
			m_count = p_num;
		};

		/*
		@ Method      : shrink_to_fit
		@ Description : change the size of array
		@ Date        : 05/27/2017 | 6:16 PM
		@ Method      : -------------------
		Change the capacity of the
		array by m_count, than set the capacity
		by m_count
		*/
		void shrink_to_fit() {
			reserve(m_count);
			m_capacity = m_count;
		}

		/*
		@ Method      : clear
		@ Description : clear the array
		@ Date        : 05/27/2017 | 7:52 AM
		@ Method      : Nope tbh
		*/
		void clear() {
			m_count = 0;
			m_capacity = 0;

			m_array = nullptr;
		};

		/*
		@ Method      : erase
		@ Description : erase elements from p_begin to p_end
		@ Date        : 05/27/2017 | 9:04 AM
		@ Method      : move the memory from the past - end
		of the delete to the begin of the
		delete pointer. To easy understand:

		0 1 2 3 5 6

		if we want to erase the element 3 to 5,
		which means 2, 3, 5, get the number of element
		remains not delete by get end() - p_end, than move:

		0 1 |2 3 5| 6

		Remaining end() - p_end = 1

		Command:
		mem_move_c(3, 5+1, 1);

		Append resuly:

		0 1 6 3 5 6

		Delete the size by p_end - p_begin + 1

		Result:

		0 1 6
		*/
		void erase(Iterator p_begin, Iterator p_end) {
			mem_move_c(p_begin, p_end + 1, (end() - p_end) * sizeof(T));
			m_count -= p_end - p_begin + 1;

		}

		/*

		@ Method      : erase
		@ Description : erase elements at p_pos
		@ Date        : 05/27/2017 | 9:04 AM
		@ Method      : erase with m_end = m_begin + 1
		*/

		void erase(Iterator p_pos) {
			erase(p_pos, p_pos + 1);
		}

		/*

		@ Method      : erase
		@ Description : erase elements at p_pos
		@ Date        : 05/27/2017 | 9:04 AM
		@ Method      : erase with m_end = m_begin + 1
		*/

		void erase(uint32 p_pos) {
			erase(begin() + p_pos);
		}

		/*

		@ Method      : erase
		@ Description : erase elements from m_begin to m_end
		@ Date        : 05/27/2017 | 9:04 AM
		@ Method      : erase with m_end = m_begin + 1
		*/

		void erase(uint32 p_begin, uint32 p_end) {
			erase(begin() + p_begin, begin() + p_end);
		}

		/*

		@ Method      : insert
		@ Description : insert data from p_begin to p_end
		@ Date        : 06/06/2017 | 1:29 PM
		@ Method      :
		caculate if the capacity is enough, or else
		reserve it.
		Then we move the part (from p_begin to the end
		of the array) to the p_end
		Then, there will be space for the data. Parse the
		data there.
		*/

		void insert(T data, Iterator p_begin, Iterator p_end) {

			int32 t_new_size = p_end - p_begin;

			if (m_count + t_new_size >= m_capacity) {
				reserve(m_count + t_new_size + 5);
			}

			mem_move_c(p_end, p_begin, (end() - p_begin) * sizeof(T));

			Iterator t_begin = p_begin;

			for (uint32 i = 0; i < p_end - p_begin; i++) {
				*t_begin++ = data;
			}

			m_count += t_new_size;
			m_capacity = m_count + t_new_size + 5;
		}

		/*

		@ Method      : insert
		@ Description : insert data at p_pos
		@ Date        : 06/06/2017 | 1:31 PM
		@ Method      :
		Wrapper
		*/
		void insert(T data, Iterator p_pos) {
			insert(data, p_pos, p_pos + 1);
		}

		/*

		@ Method      : insert
		@ Description : insert data from p_begin to p_end
		@ Date        : 06/06/2017 | 1:31 PM
		@ Method      :
		Wrapper
		*/
		void insert(T data, uint32 p_begin, uint32 p_end) {
			insert(data, begin() + p_begin, begin() + p_end);
		}

		/*

		@ Method      : insert
		@ Description : insert data at p_pos
		@ Date        : 06/06/2017 | 1:31 PM
		@ Method      :
		Wrapper
		*/
		void insert(T data, uint32 p_pos) {
			insert(data, p_pos);
		}

		/*
		@ Method      : is_empty
		@ Description : check if the array is empty
		@ Date        : 05/27/2017 | 7:52 AM
		@ Method      : Not really. Only checks if size is 0
		*/
		bool is_empty() {
			return (m_count == 0);
		}


		/*
		@ Operator    : =
		@ Date        : 05/27/2017 | 7:52 AM
		@ Method      : Nah.
		*/
		void operator = (container_base &m_para) {
			Allocator::free(m_array);

			m_count = m_para.m_count;
			m_capacity = m_para.m_capacity;

			m_array = Allocator::alloc(m_capacity * sizeof(T));

			mem_copy(m_array, m_para.m_array, m_count * sizeof(T));

		}
	};

}