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
	void swap(T& m_para1, T& m_para2) {
		T m_temp(m_para1);
		m_para1 = m_para2;
		m_para2 =  m_temp;
	}

}