
#include "c11.h"

ClassA& ClassA::operator=(const ClassA& a)
{
	return *this;
}

void listinitialization()
{
	// 1 C++98中{}的初始化问题
	// 在C++98中，标准允许使用花括号{}对数组元素进行统一的列表初始值设定。
	{
		int array1[] = { 1,2,3,4,5 };
		int array2[5] = { 0 };

		//对于一些自定义的类型，却无法使用这样的初始化。
		vector<int> v{ 1,2,3,4,5 };//C++98无法编译
		//就无法通过编译，导致每次定义vector时，都需要先把vector定义出来，然后使用循环对其赋初始值，非常不方便。
	}

	//C++11扩大了用大括号括起的列表(初始化列表)的使用范围，使其可用于所有的内置类型和用户自定义的类型，使用初始化列表时，可添加等号(= )，也可不添加。
	// 2 内置类型的列表初始化
	{
		// 内置类型变量
		int x1 = { 10 };
		int x2{ 10 };//建议使用原来的
		int x3 = 1 + 2;
		int x4 = { 1 + 2 };
		int x5{ 1 + 2 };
		// 数组
		int arr1[5]{ 1,2,3,4,5 };
		int arr2[]{ 1,2,3,4,5 };
		// 动态数组，在C++98中不支持
		int* arr3 = new int[5]{ 1,2,3,4,5 };
		// 标准容器
		vector<int> v{ 1,2,3,4,5 };//这种初始化就很友好，不用push_back一个一个插入
		map<int, int> m{ {1,1}, {2,2,},{3,3},{4,4} };

		map<int, int> m2 = { {1,1}, {2,2,},{3,3},{4,4} };

		//注意：列表初始化可以在{}之前使用等号，其效果与不使用=没有什么区别。
	}

	//标准库支持单个对象的列表初始化
	{
		class Point
		{
		public:
			Point(int x = 0, int y = 0) : _x(x), _y(y)
			{}
		private:
			int _x;
			int _y;
		};

		Point p = { 1, 2 };
		Point p2{ 1, 2 };//不建议

	}

	//多个对象的列表初始化
	{
		//多个对象想要支持列表初始化，需给该类(模板类)添加一个带有initializer_list类型参数的构造函数即可。
		//注意：initializer_list是系统自定义的类模板，该类模板中主要有三个方法：begin()、end()迭代器以及获取区间中元素个数的方法size()
		class Date
		{
		public:
			Date(int year = 0, int month = 1, int day = 1)
				:_year(year)
				, _month(month)
				, _day(day)
			{
				cout << "这是日期类" << endl;
			}

		private:
			int _year;
			int _month;
			int _day;
		};


		//C++11容器都实现了带有initializer_list类型参数的构造函数
		vector<Date> vd = { { 2021, 1, 11 }, Date{ 2022, 2, 12 }, { 2023, 3, 13 } };
		int size = vd.size();
	}

}


#include <initializer_list>
template <class T>
class Vector {
public:
	// ...    
	Vector(initializer_list<T> l) : _capacity(l.size()), _size(0)
	{
		_array = new T[_capacity];
		for (auto e : l)
			_array[_size++] = e;
	}

	Vector<T>& operator=(initializer_list<T> l) {
		delete[] _array;
		size_t i = 0;
		for (auto e : l)
			_array[i++] = e;
		return *this;
	}
	// ...
private:
	T* _array;
	size_t _capacity;
	size_t _size;
};
template <class T>
class Vector2 {
public:
	//Vector2() : _capacity(0), _size(0)
	//{
	//	_array = NULL;
	//}
private:
	T* _array;
	size_t _capacity;
	size_t _size;
};
void listinitialization2()
{
	//多个对象的列表初始化2
	{
		//多个对象想要支持列表初始化，需给该类(模板类)添加一个带有initializer_list类型参数的构造函数即可。
		//	注意：initializer_list是系统自定义的类模板，该类模板中主要有三个方法：begin()、end()迭代器以及获取区间中元素个数的方法size()。

		Vector<int> vin{ 5,4,3,2,2,1 };

		//Vector2<int> vin2{ 5,4,3,2,2,1 };   //错误	C2440	“初始化” : 无法从“initializer list”转换为“Vector2<int>”

	}
}


void error_msg(initializer_list<string> str)      //可变参数，所有参数类型一致
{
	for (auto beg = str.begin(); beg != str.end(); ++beg)
		cout << *beg << " ";
	cout << endl;
}
void listinitialization3()
{
	//initializer_list<T> lst;
	////默认初始化；T类型元素的空列表
	//initializer_list<T> lst{ a,b,c... };
	////lst的元素数量和初始值一样多；lst的元素是对应初始值的副本
	//lst2(lst);
	//lst3 = lst;
	//	//拷贝或赋值一个initializer_list对象不会拷贝列表中的元素；拷贝后，原始列表和副本元素共享
	//lst.size();  //列表中的元素数量
	//lst.begin();  //返回指向lst中首元素的指针
	//lst.end();   //返回指向lst中尾元素下一位置的指针


	//C++标准中一个非常轻量级的表示初始化器列表的类模板initializer_list及有关函数。
	//为了编写能够处理不同数量实参（但是类型相同），C++11新标准提供了initializer_list的方法。
	//与vector不同的是，initializer_list对象中的元素永远是常量值，我们无法改变initializer_list对象中元素的值。
	//在进行函数调用的时候需要使用花括号将所有的参数括起来。

	string error1 = "error1";
	string well = "well";
	//调用
	error_msg({ "hello","error",error1 });     //error为string类型
	error_msg({ "hello2",well });         //well为string类型
}



void auto2()
{
	//在定义变量时，必须先给出变量的实际类型，编译器才允许定义，但有些情况下可能不知道需要实际类型怎么给，或者类型写起来特别复杂，比如：

	short a = 32670;
	short b = 32670;

	// c如果给成short，会造成数据丢失，如果能够让编译器根据a+b的结果推导c的实际类型，就不会存在问题
	short c = a + b;
	auto d = a + b;
	std::map<std::string, std::string> m{ { "apple", "苹果" }, { "banana", "香蕉" } };
	// 使用迭代器遍历容器, 迭代器类型太繁琐
	std::map<std::string, std::string>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << " " << it->second << endl;
		++it;
	}
	auto its = m.begin();
	while (its != m.end())
	{
		cout << its->first << " " << its->second << endl;
		++its;
	}

	//C++11中，可以使用auto来根据变量初始化表达式类型推导变量的实际类型，可以给程序的书写提供许多方便。将程序中c与it的类型换成auto，程序可以通过编译，而且更加简洁。
}


void* GetMemory(size_t size)
{
	return malloc(size);
}
template<class T1, class T2>
T1 Add(const T1& left, const T2& right)
{
	return left + right;
}
void decltype2()
{
	//1 为什么需要decltype
	//auto使用的前提是：必须要对auto声明的类型进行初始化，否则编译器无法推导出auto的实际类型。
	//但有时候可能需要根据表达式运行完成之后结果的类型进行推导，因为编译期间，代码不会运行，此时auto也就无能为力。

	//如 上面的模板 T1 Add(const T1& left, const T2& right)
	//如果能用加完之后结果的实际类型作为函数的返回值类型就不会出错，
	//但这需要程序运行完才能知道结果的实际类型，即RTTI(Run - Time Type Identiﬁcation 运行时类型识别)。

	//2 decltype
	//decltype是根据表达式的实际类型推演出定义变量时所用的类型，比如：

	//推演表达式类型作为变量的定义类型
	double a = 10.9887;
	int b = 20;

	// 用decltype推演a+b的实际类型，作为定义c的类型
	decltype(a + b) c;
	c = a + b;
	cout << typeid(c).name() << endl;             // double
	cout << c << endl;                            // 30.98807


	//推演函数返回值的类型
	// 如上面的函数GetMemory

	// 如果没有带参数，推导函数的类型
	cout << typeid(decltype(GetMemory)).name() << endl;   // void * __cdecl(unsigned int)	

	// 如果带参数列表，推导的是函数返回值的类型,注意：此处只是推演，不会执行函数
	cout << typeid(decltype(GetMemory(0))).name() << endl;  // void*
}

void for2()
{
	// 基于范围的for循环
	//for (元素类型 元素对象：容器对象)
	//{
	//	循环体
	//}
	//
	//如果循环体由单条语句或者单个结构块组成，可以省略花括号
	//用元素对象依次结合容器对象中的每一个元素，每结合一个元素，执行依次循环体，直至容器内的所有元素都被结合完为止.
	//不依赖于下标元素，通用
	//不需要访问迭代器，透明
	//不需要定义处理函数，简洁
}

void override2()
{
	//指定一个虚函数覆盖另一个虚函数
	//检查派生类虚函数是否重写了基类某个虚函数，如果没有重写编译报错

	class A
	{
		virtual void foo() {};
		void bar() {};
	};

	class B : A
	{
		//void foo() const override; // 错误：B::foo 不覆盖 A::foo
								   // （签名不匹配）
		void foo() override {}; // OK：B::foo 覆盖 A::foo
		//void bar() override; // 错误：A::bar 非虚
		//void bar2() override; // 错误：A::bar2 不存在
	};

	//override作用是帮助检查是否继承了想要继承的虚函数。
	//可以避免出现 “在继承的时候写错了函数（参数类型、参数个数不符），编译没问题但是程序运行时和预想的不一样” 的情况。
	//建议重写虚函数的时候加上 override。
}

void final2()
{
	//作用：指定某个虚函数不能在子类中被覆盖，或者某个类不能被子类继承。

	class Base
	{
		virtual void foo() {};
	};

	class A : Base
	{
		void foo() final {}; // Base::foo 被覆盖而 A::foo 是最终覆盖函数
		//void bar() final; // 错误：非虚函数不能被覆盖或是 final
	};

	class B final : A // class B 为 final
	{
		//void foo() override; // 错误：foo 不能被覆盖，因为它在 A 中是 final
	};

	//class C : B // 错误：B 为 final
	//{
	//};
}

#include <array>
void array2()
{
	//增加容器—静态数组array、forward_list以及unordered系列

	/*
	array 是一个类似vector的容器，但是是保存在栈区的，因此性能更好，不能够隐式转换为指针
	编译时创建固定大小数组，只需要指定类型和大小即可
	*/
	array<int, 5>  arr = { 1, 2, 3, 4, 5 };//长度必须是常量或者常量表达式
	int* parr = &arr[0];
	parr = arr.data();
	parr = nullptr;//转换为指针的操作
	//forward_list<int> flist;
	//区别于list双向链表的单向链表，空间利用率和速率都更高
	/*
	新增两组无序容器：
	unordered_map
	unordered_multimap
	unordered_set
	unordered_multiset
	不同于set和map内部通过红黑树实现，而是hash表实现
	*/
}

void tuple2()
{
	//就像一个可以容纳不同类型的结构体
	tuple<int, double, string> tps(12, 17.58, "pixel");
	auto tp = make_tuple(5, 12.125, "hello");//构造元组，类型推断为tuple<int,double,string>
	cout << get<2>(tp) << endl;//获取元素，无法使用变量下标    // hello
	int id;
	double bim;
	string item;
	tie(id, bim, item) = tp;//元组拆包
	cout << id << " " << bim << " " << item << endl;         // 5 12.125 hello
	auto ntp = tuple_cat(tps, tp);//元组的连接
	/*
	pair，一个两个成员的结构体
	*/
	auto p1 = make_pair(12, 'c');
	pair<double, int> p2(12.125, 17);
	cout << p2.first << " " << p2.second << endl;            // 12.125 17
	p2 = make_pair(1, 1.2);
	p2 = p1;//一个含有成员函数的结构体
	//pair可以使用typedef进行简化声明
}

void default2()
{
	//在C++中对于空类编译器会生成一些默认的成员函数，
	//比如：构造函数、拷贝构造函数、运算符重载、析构函数和& 和const& 的重载、移动构造、移动拷贝构造等函数。
	//如果在类中显式定义了，编译器将不会重新生成默认版本。
	//有时候这样的规则可能被忘记，最常见的是声明了带参数的构造函数，必要时则需要定义不带参数的版本以实例化无参的对象。
	//而且有时编译器会生成，有时又不生成，容易造成混乱，于是C++11让程序员可以控制是否需要编译器生成。

	//显式缺省函数
	//在C++11中，可以在默认函数定义或者声明时加上 = default，从而显式的指示编译器生成该函数的默认版本，用 = default修饰的函数称为显式缺省函数。

	{
		class A
		{
		public:
			A(int a) : _a(a)
			{}
			// 显式缺省构造函数，由编译器生成
			A() = default;

			// 在类中声明，在类外定义时让编译器生成默认赋值运算符重载
			//A& operator=(const A& a);                   // 局部类中必选在类内实现 如下
			A& operator=(const A& a) { return *this; };
		private:
			int _a;
		};
		//A& A::operator=(const A& a) { return *this; };  // 局部类中必选在类内实现 不能在外部实现 全局类可以 如 开始的ClassA
		//A& A::operator=(const A & a) = default;         // 局部类中必选在类内实现 不能在外部实现 全局类可以 如 开始的ClassA
		A a1(10);
		A a2;
		a2 = a1;
	}


	//删除默认函数
	//如果能想要限制某些默认函数的生成，在C++98中，是该函数设置成private，并且不给定义，这样只要其他人想要调用就会报错。
	//在C++11中更简单，只需在该函数声明加上 = delete即可，该语法指示编译器不生成对应函数的默认版本，称 = delete修饰的函数为删除函数。
	{
		class A
		{
		public:
			A(int a) : _a(a)
			{}

			// 禁止编译器生成默认的拷贝构造函数以及赋值运算符重载
			A(const A&) = delete;
			A& operator=(const A&) = delete;
		private:
			int _a;
		};

		A a1(10);		
		//A a2(a1);  // 编译失败，因为该类没有拷贝构造函数		
		A a3(20);
		//a3 = a2;   // 编译失败，因为该类没有赋值运算符重载
	}
}

#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>
#include<iostream>
//固定线程数的线程池。
class FixedThreadPool
{
public:
	explicit FixedThreadPool(size_t threadCount) : _data(std::make_shared<data>())
	{
		for (size_t i = 0; i < threadCount; ++i)
		{
			std::thread([data = _data]
				{
					std::unique_lock<std::mutex> guard(data->_mutex);
					for (;;)
					{
						if (!data->_tasks.empty())
						{
							std::function<void()> currentTask = std::move(data->_tasks.front());
							data->_tasks.pop();
							guard.unlock();
							currentTask();
							guard.lock();
						}
						else if (data->_isShutdown)
						{
							break;
						}
						else
						{
							data->_condition.wait(guard);
						}
					}
				}).detach();
		}
	}

	FixedThreadPool() = default;
	FixedThreadPool(FixedThreadPool&&) = default;

	~FixedThreadPool()
	{
		if ((bool)_data)
		{
			{
				std::lock_guard<std::mutex> guard(_data->_mutex);
				_data->_isShutdown = true;
			}
			_data->_condition.notify_all();
		}
	}

	template <class F>
	void execute(F&& task)
	{
		{
			std::lock_guard<std::mutex> guard(_data->_mutex);
			_data->_tasks.emplace(std::forward<F>(task));
		}
		_data->_condition.notify_one();
	}

private:
	struct data
	{
		std::mutex _mutex;
		std::condition_variable _condition;
		bool _isShutdown = false;
		std::queue<std::function<void()>> _tasks;
	};
	std::shared_ptr<data> _data;
};
void printTest()
{
	std::cout << "Thread start id = " << std::this_thread::get_id() << std::endl;
}
void threadpool()
{
	FixedThreadPool p(4);         //有4个线程的线程池
	for (int i = 0; i < 10; i++)  //初始化10个任务
	{
		p.execute(printTest);    //打印执行任务的线程的id
	}
	getchar();
}






