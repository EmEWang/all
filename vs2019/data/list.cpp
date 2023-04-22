#include "list.h"

#include <iostream>

namespace wjg{
	template <class type>
	node<type>::node(){
		m_next = NULL;
	}

	template <class type>
	node<type>::node(const type &key){
		m_key = key;
		m_next=NULL;
	}

	template <class type>
	node<type>* node<type>::next(){
		return m_next;
	}
	



	template<class type>
	list<type>::list(){
		m_head=NULL;
		m_tail=NULL;
		m_size=0;
	}
	
	template <class type>
	bool list<type>::insert(node<type> nd){
		node<type> nn(nd);
		if(m_head==NULL || m_tail==NULL){
			m_head=&nn;
			m_head=&nn;
			m_size=1;
			return true;
		}	

		m_tail->next() = &nn;
		m_size++;
		return true;
	}

	



}
