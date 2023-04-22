#pragma once

namespace wjg{
	template <class type>
	class node{
	public:
		node();
		node(const type &key);
		node* next();
	private:
		type m_key;
		node* m_next;
	};
	

	template <class type>
	class list {
	public:
		list();
		bool insert(node<type> nd);
		bool remove(node<type> nd);
		node<type>* next();
	private:
		node<type>* m_head;
		node<type>* m_tail;
		node<type>* m_next;
		int m_size;
	};
}
