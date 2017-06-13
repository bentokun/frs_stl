#pragma once

#include "rules.h"
#include "pair.h"
#include "swap.h"
#include "allocator.h"
#include "container_base.h"

namespace FRS {

	template <typename T1, typename T2>
	class unordered_map : public container_base<pair<T1, T2>> {
	public:
		unordered_map(unordered_map& p_map) : container_base<pair<T1, T2>>(p_map) {};
		unordered_map() : container_base() {};
		
		pair<T1, T2>& get_pair(uint32 p_pos) {
			return m_array[p_pos];
		}

		T2 operator [](T1 p_key) {
			return m_array[binary_search(0, m_count - 1, p_key)].second();
		}

		uint32 binary_search(uint32 t_left, uint32 t_right, T1 p_element) {
			uint32 t_pivot = (t_left + t_right) / 2;

			if (m_array[t_pivot].first() == p_element)
				return t_pivot;

			if (m_array[t_pivot].first() > p_element)
				return binary_search(t_left, t_pivot - 1, p_element);

			if (m_array[t_pivot].first() < p_element)
				return binary_search(t_pivot + 1, t_right, p_element);
		}

		virtual void emplace_back(T1 p_first, T2 p_last) {
			if ((m_count >= m_capacity)) {
				reserve(m_capacity + 5);
			}

			m_array[m_count++] = pair<T1, T2>(p_first, p_last);
		}
	};

	template <typename T1, typename T2>
	class map_test : public unordered_map<T1, T2> {
	public:
		map_test(map_test& p_map) : unordered_map<T1, T2>(p_map) {};
		map_test() : unordered_map<T1, T2>() {};

		//Quicksort is special tbh
		void rearrange_quick_sort(int32 left, int32 right) {

			if (right - left <= 0)
				return;
			else {
				int32 i = left; int32 j = right;
				int32 t_pivot = m_array[(left + right) / 2].first();

				do {
					while (m_array[i].first() < t_pivot) i++;
					while (m_array[j].first() > t_pivot) j--;
					if (i <= j) {
						m_array[i].swap(m_array[j]);
						i++;
						j--;
					}

				} while (i < j);


				if (left < j)
					rearrange_quick_sort(left, j);
				if (right > i)
					rearrange_quick_sort(i, right);
			}

		}

		void push_back(pair<T1, T2>& p_pair) {
			if ((m_count >= m_capacity)) {
				reserve(m_capacity + 5);
			}

			m_array[m_count++] = p_pair;
			//rearrange_quick_sort(0, m_count - 1);
		}

		void emplace_back(T1 p_first, T2 p_last) {
			if ((m_count >= m_capacity)) {
				reserve(m_capacity + 5);
			}

			m_array[m_count++] = pair<T1, T2>(p_first, p_last);
			rearrange_quick_sort(0, m_count - 1);
		}

		void pop_back() {
			m_count--;
			rearrange_quick_sort(0, m_count - 1);
		}
	};
}