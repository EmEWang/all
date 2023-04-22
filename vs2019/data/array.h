#pragma once
#include <stdio.h> 
#include <stdlib.h>

#include <iostream>
#include <iomanip>

namespace wjg
{

	template <class type>
	class array
	{
	public:
		array(int size = 0, int step = 64);
		bool pushback(type key);
		bool pushfront(type key);
		bool push(type key, int index);
		bool removeback();
		bool removefront();
		bool remove(int index);
		bool sortinsert();
		bool sortbubble();
		bool sortquick();
		void print(int size = 16);
		

		int find(type key);
		type get(int index);
		
		type operator [](int index);
	private:
		bool expand(int step = 64);
		int m_size;
		int m_total;
		type *m_pt;
		int m_step;
	};
}
