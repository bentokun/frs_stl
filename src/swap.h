#pragma once

#include "pair.h"
#include "tuple.h"

namespace FRS {

	/*
		@ Method      : Swap
		@ Description : Swap two variable
		@ Date        : 05/27/2017 | 8:34 AM
		@ Method      : store the para1 as temp
	*/
	template <typename T>
	void swap(T* m_para1, T* m_para2) {
		T m_temp = *m_para1;
		*m_para1 = *m_para2;
		*m_para2 =  m_temp;
	}

	/*
		@ Method      : Swap
		@ Description : Swap two pair
		@ Date        : 05/27/2017 | 8:34 AM
		@ Method      : diy
	*/
	template <typename T1, typename T2>
	void swap(pair<T1, T2>* m_pair1, pair<T1, T2>* m_pair2) {

		T1 m_tempKey     = m_pair1->first();
		m_pair1->first() = m_pair2->first();
		m_pair2->first() = m_tempKey;

		T2 m_tempData     = m_pair1->second();
		m_pair1->second() = m_pair2->second();
		m_pair2->second() = m_tempData;

	}

	/*
		@ Method      : swap
		@ Description : Swap two tuple
		@ Date        : 05/27/2017 | 8:34 AM
		@ Method      : diy
	*/
	template <typename T1, typename T2, typename T3>
	void swap(tuple<T1, T2, T3>* m_pair1, tuple<T1, T2, T3>* m_pair2) {
		
		T1 m_tempKey = m_pair1->first();
		m_pair1->first() = m_pair2->first();
		m_pair2->first() = m_tempKey;

		T2 m_tempData = m_pair1->second();
		m_pair1->second() = m_pair2->second();
		m_pair2->second() = m_tempData;

		T2 m_tempData2   = m_pair1->third();
		m_pair1->third() = m_pair2->third();
		m_pair2->third() = m_tempData2;

	}


}