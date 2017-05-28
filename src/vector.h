#pragma once

#include "rules.h"
#include "memory.h"
#include "swap.h"

namespace FRS {
	
	/*
		@ Class       : vector<T>
		@ Description : template class managing an array of 
						typename T
		@ Date        : 05/27/2017 | 8:34 AM
		@ Method      : Using new and delete to implement class.
	*/
	template <typename T>
	class vector {
	protected:

		T* m_array;
		uint32 m_count;
		uint32 m_capacity;

	public:

		typedef T* Iterator;

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
		Iterator end()   {
			return m_array + m_count;
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

		
		vector(uint32 m_num, T m_data) {
			m_count    = m_num;
			m_capacity = m_num;

			m_array    = new T[m_capacity];

			for (int32 i = 0; i < m_num; i++) {
				m_array[i] = m_data;
			}
		}

		vector() {
			m_array		= nullptr;
			m_count		= 0;
			m_capacity  = 0;
		}

		~vector() {
			delete[] m_array;
		}

		/*
			@ Operator    : []
			@ Description : Get the element at n_num of array
			@ Date        : 05/27/2017 | 7:57 AM
			@ Method      : Not baby.
		*/
		T operator [](uint32 m_num) {
			return m_array[m_num];
		};

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
		void push_back(T m_para) {
			if ((m_count >= m_capacity)) {
				reserve(m_capacity + 5);
			}

			m_array[m_count++] = m_para;
		};

		/*
			@ Method      : pop_back
			@ Description : delete the variable at the back of the array
			@ Date        : 05/27/2017 | 8:05 AM
			@ Method      : -------------------------------------
							Pop_back is easier. Just subtract the size by one.
		*/
		void pop_back(T m_para) {
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
		void reserve(uint32 m_new_capacity) {
			if (m_array == nullptr) {
				m_count    = 0;
				m_capacity = 0;
			}

			T*     newArray    = new T[m_new_capacity];
			uint32 newSize     = m_new_capacity < m_count ? m_new_capacity : m_count;
			if (m_count != 0)
				mem_copy(newArray, m_array, m_count * sizeof(T));

			m_capacity = m_new_capacity;
			delete[]     m_array;

			m_array = new T[m_new_capacity];

			m_array    = newArray;
		};

		/*
			@ Method      : resize
			@ Description : change the size of array
			@ Date        : 05/27/2017 | 8:26 AM
			@ Method      : -------------------
							Change the capacity of the
							array by n_num, than set the size
							by n_num
		*/
		void resize(int32 n_num) {
			reserve(n_num);
			m_count = n_num;
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
			m_count     = 0;
			m_capacity = 0;

			m_array    = nullptr;
		};

		/*
			@ Method      : erase
			@ Description : erase elements from m_begin to m_end
			@ Date        : 05/27/2017 | 9:04 AM
			@ Method      : move the memory from the past - end 
							of the delete to the begin of the 
							delete pointer. To easy understand:

							0 1 2 3 5 6

							if we want to erase the element 3 to 5, 
							which means 2, 3, 5, get the number of element
							remains not delete by get end() - m_end, than move:

							0 1 |2 3 5| 6
							
							Remaining end() - m_end = 1

							Command: 
							mem_move_c(3, 5+1, 1);

							Append resuly:

							0 1 6 3 5 6

							Delete the size by m_end - m_begin + 1

							Result:

							0 1 6
		*/
		void erase(Iterator m_begin, Iterator m_end) {
			uint32 a = end() - m_end - 1;
			mem_move_c(m_begin, m_end + 1, (end() - m_end) * sizeof(T));
			m_count -= m_end - m_begin + 1;

		}

		/*
			
			@ Method      : erase
			@ Description : erase elements from m_begin to m_end
			@ Date        : 05/27/2017 | 9:04 AM
			@ Method      : erase with m_end = m_begin + 1
		*/

		void erase(Iterator m_begin) {
			erase(m_begin, m_begin + 1);
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
		vector<T> operator = (vector<T> m_para) {
			delete[] m_array;

			m_count		= m_para.m_count;
			m_capacity  = m_para.m_capacity;

			m_array		= new T[m_capacity];

			for (uint32 i = 0; i < m_count; i++) {
				m_array[i] = m_para.m_array[i];
			}
		}
	};

}