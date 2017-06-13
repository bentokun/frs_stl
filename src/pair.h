#pragma once

namespace FRS {


	template <typename T1, typename T2>
	struct pair {
	protected:
		T1 m_key;
		T2 m_data;

	public:
		
		pair() { };

		pair(T1 m_parakey, T2 m_paradata) {
			m_key = m_parakey;
			m_data = m_paradata;
		}

		pair(pair& p_pair) {
			m_data = p_pair.m_data;
			m_key = p_pair.m_key;
		}

		void operator = (pair<T1, T2>& m_pair) {
			m_data = m_pair.m_data;
			m_key  = m_pair.m_key;
		} 

		T1& first() {
			return m_key;
		}

		T2& second() {
			return m_data;
		}

		bool operator == (pair<T1, T2> m_pair) {
			return (m_key == m_pair.m_key &&
				m_data == m_pair.m_data);
		}

		bool operator != (pair<T1, T2> m_pair) {
			return (m_key != m_pair.m_key &&
				m_data != m_pair.m_data);
		}

		bool operator < (pair<T1, T2> m_pair) {
			return (m_key < m_pair.m_key) ||
				(!(m_key <m_pair.m_key)) && 
				( m_data < m_pair.m_data);
		}

		bool operator > (pair<T1, T2> m_pair) {
			return !(*this < m_pair)
		}

		bool operator <= (pair<T1, T2> m_pair) {
			return (*this < m_pair) || (*this == m_pair);
		}

		bool operator >= (pair<T1, T2> m_pair) {
			return (*this > m_pair) || (*this == m_pair);
		}

		void swap(pair<T1, T2>& m_pair) {

			T1 m_tempKey(m_key);
			m_key = m_pair.m_key;
			m_pair.m_key = m_tempKey;

			T2 m_tempData(m_data);
			m_data = m_pair.m_data;
			m_pair.m_data = m_tempData;

		};


	};

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1& m_parakey, T2& m_paradata) {
		return pair<T1, T2>(m_parakey, m_paradata);
	};

}