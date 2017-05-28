#pragma once

#include "Pair.h"

namespace FRS {

	template <typename T>
	void swap(T* m_para1, T* m_para2) {
		T m_temp = *m_para1;
		*m_para1 = *m_para2;
		*m_para2 =  m_temp;
	}

	template <typename T1, typename T2>
	void swap(Pair<T1, T2>* m_pair1, Pair<T1, T2>* m_pair2) {

		T1 m_tempKey     = m_pair1->m_key;
		m_pair1->m_key   = m_pair2->m_key;
		m_pair2->m_key   = m_pair1->m_tempKey;

		T2 m_tempData    = m_pair1->m_data;
		m_pair1->m_data  = m_pair2->m_data;
		m_pair2->m_data  = m_pair1->m_tempData;

	}

}