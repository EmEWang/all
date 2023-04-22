#include "array.h"
#include <stdio.h>

//

namespace wjg {
	template <class type>
	array<type>::array(int size, int step)
	{
		m_size = 0;
		m_step = step;
		m_total = size + step;
		m_pt = (type*)malloc((size + step) * sizeof(type));
	}

	template<class type>
	bool array<type>::pushback(type key)
	{
		if (m_pt == NULL)
		{
			return false;
		}

		if(m_size < m_total){
			*(m_pt + m_size ) = key;
			m_size++;
		}
		else {
			if(expand()){
				*(m_pt + m_size) = key;
				m_size++;
			}
			else
				return false;
		}
			
		return true;
	}
}

template <class type>
bool wjg::array<type>::pushfront(type key)
{
	if(m_size < m_total){
		memmove(m_pt+sizeof(type), m_pt, m_size * sizeof(type));
		*(type*)(m_pt) = key;
	}
	else{
		if(expand()){
			memmove(m_pt+sizeof(type), m_pt, m_size * sizeof(type));
			*(type*)(m_pt) = key;
		}
		else
			return false;
	}

	return true;
}

template <class type>
bool wjg::array<type>::push(type key, int index){
	if(index < 0 || index > m_size)
		return false;
	if(m_size < m_total){
		memmove(m_pt + (index + 1) * sizeof(type), m_pt + index * sizeof(type), (m_size - index) * sizeof(type));
		*(type*)(m_pt + index * sizeof(type));
	}
	else{
		if(expand()){
			memmove(m_pt + (index + 1) * sizeof(type), m_pt + index * sizeof(type), (m_size - index) * sizeof(type));
			*(type*)(m_pt + index * sizeof(type));
		}
		else
			return false;
	}
	return true;
}

template <class type>
bool wjg::array<type>::removeback(){
	if(m_size > 0)
		m_size--;

	return true;
}

template <class type>
bool wjg::array<type>::removefront(){
	if(m_size > 0){
		memmove(m_pt +  sizeof(type), m_pt +  * sizeof(type), m_size * sizeof(type));
		*(type*)(m_pt +  sizeof(type));
	}
		
	return true;
}

template <class type>
bool wjg::array<type>::remove(int index){
	if(index < 0 || index > m_size)
		return false;
	if(m_size > 0){
		memmove(m_pt + index * sizeof(type), m_pt + (index + 1) * sizeof(type),  sizeof(type));
		m_size--;
	}
	return true;
}

template <class type>
int wjg::array<type>::find(type key){
	for(int i =0 ; i < m_size; ++i){
		if(*(type*)(m_pt + i * sizeof(type)) == key)
			return i;
	}
	return -1;
}

template <class type>
type wjg::array<type>::get(int index){
	if(index < 0 || index > m_size)
		return 0;
	return *(type*)(m_pt + index * sizeof(type));
}

template<class type>
type wjg::array<type>::operator[](int index)
{
	return *(m_pt + index);
}


template <class type>
bool wjg::array<type>::expand(int step ){
	void * temp = realloc(m_pt, (m_total + step) * sizeof(type));
	if(temp == NULL)
		return false;
	m_pt = (type*)temp;
	m_total += step;
	return true;
}

template <class type>
void wjg::array<type>::print(int size)
{
	for(int i = 0; i < size; ++i){
		printf("%9x# ", i);
	}

	printf("\n");
	
	for(int i = 0;i < m_size; ++i)
	{
		std::cout << std::setw(10) << m_pt[i] << ' ';
		if( (i+1) % size == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;
}

template <class type>
bool wjg::array<type>::sortinsert()
{
	for(int i = 1; i < m_size; ++i)
	{
		type temp = m_pt[i];
		int j = 0;
		for(j = i ; j > 0; --j){
			if(temp < m_pt[j-1]){
				m_pt[j] = m_pt[j-1];
				continue;
			}	
			
			break;
		}
		m_pt[j] = temp;
	}

	return true;
}

template <class type>
bool wjg::array<type>::sortbubble(){
	for(int i = 0; i < m_size; ++i){
		int index = i;
		for(int j = i + 1; j < m_size; ++j){
			if(m_pt[index] > m_pt[j])
				index = j;
		}
		type t = m_pt[index];
		m_pt[index] = m_pt[i];
		m_pt[i] = t;
	}
	
	return true;
}

template <class type>
bool wjg::array<type>::sortquick(){
	return true;
}
