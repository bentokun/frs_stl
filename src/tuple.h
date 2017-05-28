#pragma once

#include "pair.h"

namespace FRS {

	/*
		@ Class       : Tuple<T1, T2, T3>
		@ Description : 3d struct
		@ Date        : 05/27/2017 | 8:34 AM
	*/
	template <typename T1, typename T2, typename T3>
	struct tuple {
	protected:

		T1           m_key	{};
		pair<T2, T3> m_data {};

	public:

		tuple() {};

		tuple(T1 m_para1, T2 m_para2, T3 m_para3) {
			m_key			= m_para1;
			m_data			= make_pair(m_para2, m_para3);
		}

		tuple(T1 m_para1, pair<T2, T3> m_para2) {
			m_key			= m_para1;
			m_data			= m_para2;
		}

		/*
			@ Method      : first
			@ Description : Get/set of the key
			@ Date        : 05/27/2017 | 8:34 AM
		*/
		T1& first() {
			return m_key;
		}

		/*
			@ Method      : second
			@ Description : Get/set of the data->first()
			@ Date        : 05/27/2017 | 8:34 AM
		*/
		T2& second() {
			return m_data.first();
		}

		/*
			@ Method      : third
			@ Description : Get/set of the data->second()
			@ Date        : 05/27/2017 | 8:34 AM
		*/
		T3& third() {
			return m_data.second();
		}

		/*
			@ Method      : sec_and_third
			@ Description : Pointer to the m_data. Unstable and
							shouldn't be used often.
			@ Date        : 05/27/2017 | 8:34 AM
		*/
		pair<T2, T3>* sec_and_third() {
			return m_data;
		}

		/*
			@ Method      : first_and_sec
			@ Description : Pair of first and second element
			@ Date        : 05/27/2017 | 8:34 AM
		*/
		pair<T1, T2> first_and_sec() {
			return make_pair(m_key, m_data.first());
		}

		/*
			@ Method      : first_and_third
			@ Description : Pair of first and third element
			@ Date        : 05/27/2017 | 8:34 AM
		*/
		pair<T1, T3> first_and_third() {
			return make_pair(m_key, m_data.second());
		}

		/*
			@ Operator    : =
			@ Description : Equal? Idk
			@ Date        : 05/27/2017 | 8:34 AM
		*/
		tuple<T1, T2, T3> operator = (tuple<T1, T2, T3> m_pair) {
			tuple<T1, T2, T3> m_temppair;

			m_temppair.m_data = m_pair.m_data;
			m_temppair.m_key = m_pair.m_key;

			return m_temppair;
		}

		/*
			@ Operator    : ==
			@ Description : Check equality of each object
			@ Date        : 05/27/2017 | 8:34 AM
		*/
		bool operator == (tuple<T1, T2, T3> m_tuple) {
			return (m_key == m_tuple.m_key &&
				m_data == m_tuple.m_data);
		}

		/*
			@ Operator    : !=
			@ Description : ! Check equality of each object
			@ Date        : 05/27/2017 | 8:34 AM
		*/
		bool operator != (tuple<T1, T2, T3> m_tuple) {
			return !(m_tuple == *this);
		}

		bool operator < (tuple<T1, T2, T3> m_tuple) {
			return (m_key < m_tuple.m_key ||
				(!(m_key < m_tuple.m_key)) && m_data < m_tuple.m_data);
		}

		bool operator > (tuple<T1, T2, T3> m_tuple) {
			return !((*this) < m_tuple);
		}

		bool operator <= (tuple<T1, T2, T3> m_tuple) {
			return ((*this) < m_tuple) || ((*this) == m_tuple);
		}

		bool operator >= (tuple<T1, T2, T3> m_tuple) {
			return !((*this) < m_tuple) || ((*this) == m_tuple);
		}
		
	};

	template <typename T1, typename T2, typename T3>
	tuple<T1, T2, T3> make_tuple(T1 m_para1, T2 m_para2, T3 m_para3) {
		tuple<T1, T2, T3> m_temptuple;

		m_temptuple.first() = m_para1;
		m_temptuple.second() = m_para2;
		m_temptuple.third() = m_para3;

		return m_temptuple;
	}

	template <typename T1, typename T2, typename T3>
	tuple<T1, T2, T3> make_tuple(T1 m_para1, pair<T2,T3> m_para2) {
		tuple<T1, T2, T3> m_temptuple;

		m_temptuple.first() = m_para1;
		m_temptuple.second() = m_para2.first();
		m_temptuple.third() = m_para2.second();

		return m_temptuple;
	}
}