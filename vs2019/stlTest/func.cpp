#include "func.h"


void map1()
{
}

void insertIterator()
{
	auto func1 = [](list<int> lst)
	{
		//for each( auto it1 : lst)  //错误
		for( auto it1 : lst)
		{
			cout << it1 << " ";
		}
		cout << endl;
	};

	list<int> lst1;
	lst1.push_back(1);
	lst1.push_back(2);
	lst1.push_back(3);
	func1(lst1);

	list<int>::iterator it1 = lst1.begin();
	//it = 11；             // 错误
	*(it1) = 11;
	func1(lst1);
}

void insertIteratorOut()
{
	vector<string> vct1;
	vct1.push_back("ab");
	vct1.push_back("cd");
	vct1.push_back("ef");
	auto it = vct1.begin();
	cout << *it << endl;

	vector<int> vct2;
	vct2.push_back(1);
	vct2.push_back(2);
	vct2.push_back(3);
	auto it2 = vct2.begin();
	//cout << it2 << endl;    //错误
	cout << *it2 << endl;

	list<int> lst1;
	lst1.push_back(1);
	lst1.push_back(2);
	lst1.push_back(3);
	auto it3 = lst1.begin();
	//cout << it3 << endl;
	cout << *it3 << endl;
}

void insertFunc1()
{
	list<int> lst1;
	list<int> lst2;

	for (int i = 1; i < 9; ++i)
	{
		lst1.push_back(i);
	}

	auto func = [](list<int> lst)
	{
		for (auto i : lst)
		{
			cout << i << " ";
		}

		cout << endl;
	};

	lst2.clear();
	copy_if(lst1.begin(), lst1.end(), back_inserter(lst2), bind2nd(greater<int>(), 5));   // > 5 
	func(lst2);

	lst2.clear();
	copy_if(lst1.begin(), lst1.end(), back_inserter(lst2), not1(bind2nd(greater<int>(), 5)));  // <=5
	func(lst2);

	lst2.clear();
	copy_if(lst1.begin(), lst1.end(), back_inserter(lst2), bind2nd(modulus<int>(), 2));        // 奇数
	func(lst2);
}



void testmap()
{
	//map中用[]访问元素
	//若该key存在，则访问取得value值；
	//若该key不存在，访问仍然成功，取得value对象默认构造的值。具体如下：
	//用[]访问，但key不存在时，C++会利用该key及默认构造的value，组成{ key，value }对，插入到map中。
	//value为 string对象，则构造空串；value为int对象，构造为0。
	//注：因此在访问map元素时，应先用map.find查找该元素，找到后再访问。 同时，用法mymap2["str"]++; 常用于词频统计，存在则加一，不存在则创建后赋值为1。
	//
	//Map中的元素是自动按key升序排序
	//
	//map中元素的删除：
	//(1)   my_Map.erase(my_Itr);
	//(2)   my_Map.erase("c");
	//还是注意，第一种情况在迭代期间是不能被删除的，道理和foreach时不能删除元素一样。
	//
	//
	//map<string,itemS>::iterator   it; 
	//for (it = mymap.begin(); it != mymap.end(); it++)
	//{
	//	if (it->second.a > 100)
	//	{
	//		i = mymap.erase(it);  ----->正确
	//			mymap.erase(it);     ----->it失效..
	//	}
	//}
	//
	// C98    1 3 不返回值
	//(1)	void erase(iterator position);
	//(2)	size_type erase(const key_type & k);   //返回删除的数量
	//(3)	void erase(iterator first, iterator last);
	//
	// C11   1 3返回  return an iterator to the element that follows the last element removed (or map::end, if the last element was removed).
	//(1)	iterator  erase(const_iterator position);
	//(2)	size_type erase(const key_type & k);   //返回删除的数量
	//(3)	iterator  erase(const_iterator first, const_iterator last);
	//

	{
		std::map<string, void*> map1;
		int i1 = 11;
		int i2 = 12;
		int i3 = 13;
		map1["111"] = &(i1);
		map1["222"] = &(i2);
		map1["333"] = &(i3);

		//1
		for (auto it = map1.begin(); it != map1.end(); ++it)
		{
			if (*((int*)(it->second)) == 11)
			{
				auto it2 = map1.erase(it);
				printf("[%s-%s]\n", "11", (it2 == map1.end()? "end":it2->first.c_str()));
				break;
			}
		}
		//2
		for (auto it = map1.begin(); it != map1.end(); ++it)
		{
			if (*((int*)(it->second)) == 12)
			{
				auto it2 = map1.erase(it);
				printf("[%s-%s]\n", "12", (it2 == map1.end() ? "end" : it2->first.c_str()));
				break;
			}
		}
		//3
		for (auto it = map1.begin(); it != map1.end(); ++it)
		{
			if (*((int*)(it->second)) == 13)
			{
				auto it2 = map1.erase(it);
				printf("[%s-%s]\n", "13", (it2 == map1.end() ? "end" : it2->first.c_str()));
				break;
			}
		}
		
		//[11-222]
		//[12-333]
		//[13-end]

		//即使是 把 1 2 注释掉 3的输出也是 故erase返回的是下一个
		//[13-end]
	}

	{
		std::map<string, void*> map1;
		int i1 = 11;
		int i2 = 12;
		int i3 = 13;
		map1["111"] = &(i1);
		map1["222"] = &(i2);
		map1["333"] = &(i3);

		auto it = map1.find("555");

		printf("[%s-%x]\n", "555", ((it == map1.end()) ? 5 : 9));   //没有key则抛出异常 out_of_range
		//[555-5]
	}
	try{
		std::map<string, void*> map1;
		int i1 = 11;
		int i2 = 12;
		int i3 = 13;
		map1["111"] = &(i1);
		map1["222"] = &(i2);
		map1["333"] = &(i3);


		printf("[%s-%x]\n", "111", map1["111"]);
		printf("[%s-%x]\n", "222", map1["222"]);
		printf("[%s-%x]\n", "333", map1["333"]);
		printf("[%s-%x]\n", "444", ((map1["444"] == NULL) ? 4 : 9));   //没有key则默认添加之 value 为null
		printf("[%s-%x]\n", "555", ((map1.at("555") == NULL) ? 5 : 9));   //没有key则抛出异常 out_of_range
		//[111 - 93fd98]
		//[222 - 93fd94]
		//[333 - 93fd90]
		//[444 - 4]
	}
	catch (const out_of_range& e) {
		cout << "Out of Range Exception at " << e.what();
	}

	{
		std::map<string, int> map1;
		int i1 = 11;
		int i2 = 12;
		int i3 = 13;
		map1["111"] = i1;
		map1["222"] = i2;
		map1["333"] = i3;


		printf("[%s-%d]\n", "111", map1["111"]);
		printf("[%s-%d]\n", "222", map1["222"]);
		printf("[%s-%d]\n", "333", map1["333"]);
		printf("[%s-%d]\n", "444", ((map1["444"] == 0) ? 4 : 9));   //没有key则默认添加之 value 为0
		//[111 - 11]
		//[222 - 12]
		//[333 - 13]
		//[444 - 4]
	}
}


void testlist()
{
	list<int> ll1;
	list<int> ll2;
	list<int> ll3;
	list<int> ll4;
	list<int> ll5;
	list<int> ll6;
	ll1.push_back(1);
	ll1.push_back(2);
	ll1.push_back(3);

	ll2.push_back(1);
	ll2.push_back(4);
	ll2.push_back(3);

	ll1.sort();
	ll1.unique();
	ll2.sort();


	set_difference(ll1.begin(), ll1.end(), ll2.begin(), ll2.end(), insert_iterator<list<int> >(ll3, ll3.begin()));      // S1 - S2
	set_union(ll1.begin(), ll1.end(), ll2.begin(), ll2.end(), back_inserter<list<int> >(ll4));                          // S1 + S2
	set_intersection(ll1.begin(), ll1.end(), ll2.begin(), ll2.end(), back_inserter(ll5));                                // S1 ^ S2
	set_symmetric_difference(ll1.begin(), ll1.end(), ll2.begin(), ll2.end(), insert_iterator<list<int> >(ll6, ll6.begin())); // S1 n S2 + S2 n S1

	printf("------------set_difference--------------\n");
	for (auto it = ll3.begin(); it != ll3.end(); ++it)
	{
		printf("%d\n", *it);
	}

	printf("------------set_union--------------\n");
	for (auto it = ll4.begin(); it != ll4.end(); ++it)
	{
		printf("%d\n", *it);
	}

	printf("------------set_intersection--------------\n");
	for (auto it = ll5.begin(); it != ll5.end(); ++it)
	{
		printf("%d\n", *it);
	}

	printf("------------set_symmetric_difference--------------\n");
	for (auto it = ll6.begin(); it != ll6.end(); ++it)
	{
		printf("%d\n", *it);
	}
}

void testlist2()
{
	list<int> lst = { 1,2,3,4,5 };
}

void testlist3()
{
	class iint {
	public:
		iint() {}
		iint(int i) { m_i = i; }
		~iint() { printf("destruct %d\n", m_i); }
		int m_i;
	};

	list<iint*> lst;
	lst.push_back(new iint(1));
	lst.push_back(new iint(2));
	
	for (auto it = lst.begin(); it!=lst.end();)
	{
		iint* pp = *it;
		lst.erase(it++);
		delete pp;
	}
	lst.clear();

	printf("testlist3 end\n");
}

bool mycompare(std::string& strA, std::string& strB) {
	int lengA = strA.length();
	int lengB = strB.length();
	if (lengA < lengB) {
		int i = strB.find(strA.c_str());
		if (i == 0) {
			if (strB.at(i + lengA) == '.') {
				return false;
			}
			else {
				return true;
			}
		}
		return strA < strB;
	}
	if (lengA == lengB) {
		return strA < strB;
	}
	else {
		int i = strA.find(strB.c_str());
		if (i == 0) {
			if (strA.at(i + lengB) == '.') {
				return true;
			}
			else {
				return false;
			}
		}
		return strA < strB;
	}
}
bool mycompare2(std::string& strA, std::string& strB) {
	int lengA = strA.length();
	int lengB = strB.length();
	if (lengA < lengB) {
		return true;
	}
	if (lengA == lengB) {
		return strA < strB;
	}
	else {
		return false;
	}
}

void testlist4()
{
	list<string> lst;
	lst.push_back("1.sd1");
	lst.push_back("1.sd1.1");
	lst.push_back("1.sd");
	lst.push_back("1.s");
	//lst.push_back("1.sd2");
	//lst.push_back("1.sd1.1.1");
	//lst.push_back("1.sd2.1");
	//lst.push_back("1.sd1.1");

	auto ff = [&lst](const string msg) {

		printf("%s\n", msg.c_str());
		int index = 0;
		for (auto i : lst)
		{
			printf("%d %s\n", ++index,i.c_str());
		}
		printf("\n");
	};

	
	ff("no sort");
	lst.sort(mycompare2);
	ff("sorted");
}

void OstreamInterator()
{
	ostream_iterator<int> ostr(cout, " ");
	*ostr = 1;
	++ostr;               // 要不要都一样 无实际意义
	*ostr = 2;
	*ostr = 3;
	cout << endl;

	typedef typename list<int> lstType; //重命名一种类型
	//typedef typename list<float> lstType; //重命名一种类型

	list<int> lst;
	for (int i =1; i < 5; ++i)
	{
		lst.push_back(i);
	}

	copy(lst.begin(), lst.end(), ostr);
	cout << endl;

	copy(lst.begin(), lst.end(), ostream_iterator<lstType::value_type>(cout, " < ")); //value_type必须使用类型 ::
	cout << endl;
}


void testtransform()
{
	list<string> lst;
	//generate_n(lst.begin(), )
	for (int i = 0; i < 5; ++i)
	{
		char temp[22];
		sprintf_s(temp, "%d", i);
		lst.push_back(temp);
	}
	copy(lst.begin(), lst.end(), ostream_iterator<string>(cout, "\n"));
	cout << endl;
	transform(lst.begin(), lst.end(), lst.begin(), [](string& str) {return "GigabitE1/0/" + str + "_GigabitEthernet1/0/" + str + " Interface"; });
	copy(lst.begin(), lst.end(), ostream_iterator<string>(cout, "\n"));
	cout << endl;

	string str2 = "1;2;44;55;66";
	list<string> lst2;
	lst2.push_back("1");
	lst2.push_back("2");
	lst2.push_back("33");
	lst2.push_back("44");
	vector<int> vct2;
	transform(lst2.begin(), lst2.end(), back_inserter(vct2), [](string str) {return atoi(str.c_str()); });
	copy(vct2.begin(), vct2.end(), ostream_iterator<int>(cout, "\n"));
	cout << endl;
}

void testlamda()
{
	//格式 [captrue] (params) opt->ret{ body };
	//其中 capture是捕获列表；params是参数列表；opt是函数选项；ret是返回值类型；body是函数体。

	{
		//lambda表达式的返回值通过返回值后置语法来定义，所以很多时候可以省略返回值类型，编译器根据return语句自动推导返回值类型。
		auto f1 = [](int a) {return a + 1; };
		//但是初始化列表不能作为返回值的自动推导，需要显示给出具体的返回值类型。
		auto f2 = [](int a) {return a + 1; };   //ok,return type is int
		//auto f2_ = []() {return { 1,2 }; };       //error:无法推导出返回值类型
		//lambda表达式在没有参数列表的时候，参数列表可以省略。
		auto f3 = []() {return 1; };
		auto f4 = [] {return 1; }; //省略空参数表
	}

	//lambda表达式可以通过捕获列表捕获一定范围内的变量：
	//[]不捕获任何变量；
	//[&]捕获外部作用域所有变量，并作为引用在函数体使用（按引用捕获）；
	//[=]捕获外部作用域作用变量，并作为副本在函数体使用（按值捕获）；
	//[=, &foo]按值捕获外部作用域所有变量，并按引用捕获foo变量；
	//[bar]按值捕获bar变量，同时不捕获其他变量；
	//[this]捕获当前类中的this指针，让lambda拥有和当前类成员函数同样的访问权限，如果已经使用了& 或者 = ，就默认添加此选项。捕获this的目的是可以在lambda中使用当前类的成员函数和成员变量。    
	{
		int a = 0, b = 2;
		//auto f1 = [] {return a; };                 //error,没有捕获外部变量
		auto f2 = [&] {return a++; };               //ok,按引用捕获所有外部变量，并对a执行自加运算
		auto f3 = [=] {return a; };                 //ok,按值捕获所有外部变量，并返回a
		//auto f4 = [=] {return a++; };               //error,按值引用不能改变值
		//auto f5 = [a] {return a + b; };             //error,没有捕获b
		auto f6 = [a, &b] {return a + (b++); };     //ok,捕获a和b的值，并对b做自加运算
		auto f7 = [=, &b] {return a + (b++); };     //ok,捕获所有外部变量和b的引用，并对b做自加运算
	}

	class A
	{
	public:
		int mi = 0;

		void func(int x, int y)
		{
			//auto x1 = [] {return mi; };                      //error,没有捕获外部变量
			auto x2 = [=] {return mi + x + y; };            //ok，按值捕获所有外部变量
			auto x3 = [&] {return mi + x + y; };            //ok,按引用捕获所有外部变量
			auto x4 = [this] {return mi; };                 //ok,捕获this指针
			//auto x5 = [this] {return mi + x + y; };         //error，没有捕获x,y
			auto x6 = [this, x, y] {return mi + x + y; };     //ok，捕获this，x，y
			auto x7 = [this] {return mi++; };               //ok,捕获this指针，并修改成员的值
		}
	};

	{
		//lambda表达式其实是一个带有operator()的类，即仿函数，因此我们可以使用std::bind和std::function来存储和操作lambda表达式：
		std::function<int(int)> f1 = [](int a) { return a; };
		std::function<int(void)> f2 = std::bind([](int a) {return a; }, 123);

		//对于没有捕获任何变量的lambda表达式，还可以被转换成一个普通的函数指针：
		using func_t = int(*)(int);                        // c11 定义新类型 语法 同typedef c11支持定义模板类型
		func_t f = [](int a) {return a; };
		f(123);		
	}

	{
		//lambda表达式可以说是定义仿函数闭包的语法糖，它捕获的任何外部变量都会转换为闭包类型的成员变量。
		//而使用成员变量的类的operator(), 如果能直接转换为普通的函数指针，那lambda表达式本身的this指针会丢失，
		//没有捕获任何外部变量的lambda表达式则不存在这个问题，所以按值捕获的外部变量无法修改。
		//因为lambda表达式中的operator()默认是const的，一个const成员函数无法修改成员变量的值，而mutable则是取消operator()的const。
		//所以，没有捕获变量的lambda表达式可以直接转换为函数指针，而捕获变量的lambda表达式则不能转换为函数指针。
		int a = 0;
		auto f1 = [=]() { return a; };                     //ok
		//auto f2 = [=]() { return a++; };                   //error 
		auto f3 = [=]() mutable { return a++; };                     //ok
		typedef void(*Ptr)(int*);                          // 定义新类型 语法
		Ptr p1 = [](int* p) {delete p; }; //ok,没有捕获的lambda表达式可以转换为函数指针
		//Ptr p2 = [&](int* p) {delete p; }; //error，有捕获的lambda表达式不能直接转换为函数指针，不能通过编译
	}

	{
		//lambda表达式的大致原理：每当你定义一个lambda表达式后，编译器会自动生成一个匿名类（这个类重载了()运算符），我们称为闭包类型（closure type）。
		//那么在运行时，这个lambda表达式就会返回一个匿名的闭包实例，是一个右值。所以，我们上面的lambda表达式的结果就是一个个闭包。对于复制传值捕捉方式，类中会相应添加对应类型的非静态数据成员。
		//在运行时，会用复制的值初始化这些成员变量，从而生成闭包。对于引用捕获方式，无论是否标记mutable，都可以在lambda表达式中修改捕获的值。至于闭包类中是否有对应成员，C++标准中给出的答案是：不清楚的，与具体实现有关。
		//lambda 表达式是不能被赋值的
		auto f1 = []() {cout << "a"; };
		auto f2 = []() {cout << "a"; };
		//f1 = f2;                 //error 无法赋值
		auto f3 = f1;              //ok    生成副本
	}

	{
		//最好不要使用[=]和[&]默认捕获所有变量。
		//默认引用捕获所有变量，你有很大可能会出现悬挂引用（Dangling references），因为引用捕获不会延长引用的变量的生命周期：
		//function<int(int)> addx(int x)
		//{
		//	return [&](int a) { return x + a; };
		//}
		//上面函数返回了一个lambda表达式，参数x仅是一个临时变量，函数add_x调用后就被销毁了，但是返回的lambda表达式却引用了该变量，当调用这个表达式时，引用的是一个垃圾值，会产生没有意义的结果。上面这种情况，使用默认传值方式可以避免悬挂引用问题。

		//但是采用默认值捕获所有变量仍然有风险，看下面的例子：
		class Filter
		{
		public:
			Filter(int divisorVal) :divisor{ divisorVal } {}
			std::function<bool(int)> getFilter()
			{
				return [=](int value) {return value % divisor == 0; };
			}
		private:
			int divisor;
		};
		//这个类中有一个成员方法，可以返回一个lambda表达式，这个表达式使用了类的数据成员divisor。
		//而且采用默认值方式捕捉所有变量。你可能认为这个lambda表达式也捕捉了divisor的一份副本，但是实际上并没有。
		//因为数据成员divisor对lambda表达式并不可见，你可以用下面的代码验证：
		// 类的方法，下面无法编译，因为divisor并不在lambda捕捉的范围
		//std::function<bool(int)> getFilter()
		//{
		//	return [divisor](int value) {return value % divisor == 0; };
		//}
		////原代码中，lambda表达式实际上捕捉的是this指针的副本，所以原来的代码等价于：
		//std::function<bool(int)> getFilter()
		//{
		//	return [this](int value) {return value % this->divisor == 0; };
		//}
		////尽管还是以值方式捕获，但是捕获的是指针，其实相当于以引用的方式捕获了当前类对象，所以lambda表达式的闭包与一个类对象绑定在一起了，这很危险，
		////因为你仍然有可能在类对象析构后使用这个lambda表达式，那么类似“悬挂引用”的问题也会产生。所以，采用默认值捕捉所有变量仍然是不安全的，主要是由于指针变量的复制，实际上还是按引用传值
		
	}
}

void testfor_each()
{
	vector<int> vct;
	for (int i = 1; i < 9 ; ++i)
	{
		vct.push_back(i);
		cout << i;
	}
	cout << endl;

	for_each(vct.begin(), vct.end(), [](int& i) {i++; });         // 引用 改变容器的值
	copy(vct.begin(), vct.end(), ostream_iterator<int>(cout, " "));  // 输出
	cout << endl;

	for_each(vct.begin(), vct.end(), [](int i) {cout << i << " < "; });  // 输出
	cout << endl;

	vector<int> vct2;
	for_each(vct.begin(), vct.end(), [&](int i) {vct2.push_back(++i); });
	transform(vct2.begin(), vct2.end(), ostream_iterator<int>(cout, " - "), [&](int i) {return i + 1; });  // 输出
	cout << endl;
}

void testcount()
{
	list<int> lst;
	for (int i = 1; i < 9; ++i)
	{
		lst.push_back(i);
		cout << i;
	}
	cout << endl;

	cout << "[num3]" << count(lst.begin(), lst.end(), 3) << endl;
	cout << "[num 3< <7]" << count_if(lst.begin(), lst.end(), [](int i) { return i > 3 && i < 7; }) << endl;
	cout << "[num3 3<]" << count_if(lst.begin(), lst.end(), bind2nd(greater<int>(), 3)) << endl;
}

void testminmax()
{
	list<int> lst;
	for (int i = 1; i < 9; ++i)
	{
		lst.push_back(i);
		cout << i;
	}
	cout << endl;

	cout << "[min]" << *min_element(lst.begin(), lst.end()) << endl;
	cout << "[min]" << *min_element(lst.begin(), lst.end(), [](int i, int j) { return (i +3)%7 < (j + 3) % 7; }) << endl;
	cout << "[min]" << *min_element(lst.begin(), lst.end(), multiplies<int>()) << endl;
	transform(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "), bind2nd(multiplies<int>(), 2));
	cout << endl;

	cout << "[max]" << *max_element(lst.begin(), lst.end()) << endl;
	cout << "[max]" << *max_element(lst.begin(), lst.end(), [](int i, int j) { return (i + 3) % 7 < (j + 3) % 7; }) << endl;
	cout << "[max]" << *max_element(lst.begin(), lst.end(), multiplies<int>()) << endl;
}

void testfindsearch()
{
	list<int> lst;
	for (int i = 1; i < 9; ++i)
	{
		lst.push_back(i);
		cout << i;
	}
	cout << endl;

	//搜寻n个连续元素
	string str = "abcccdefghijklmnopqrstuvwxyz";
	cout << "[c/3 ccc]" << *search_n(str.begin(), str.end(), 3, 'c') << endl;
	cout << "[c/3 ghi]" << *search_n(str.begin(), str.end(), 3, 'h', [](char c1, char c2) { return c2 < c1 + 2; }) << endl; // 其中 h传入c2
	cout << "[c/3 mno]" << *search_n(str.begin(), str.end(), 3, 'l', greater<char>()) << endl;

	//搜寻第一个子区间
	string substr = "klm";
	cout << "[c/3 klm]" << *search(str.begin(), str.end(), substr.begin(), substr.end()) << endl;
	cout << "[c/3 klm]" << *search(str.begin(), str.end(), substr.begin(), substr.end(), [](char c1, char c2) {return c2 == c1 - 2; }) << endl;  //mno
	cout << "[c/3 klm]" << *search(str.begin(), str.end(), substr.begin(), substr.end(), greater<char>()) << endl;                           //lmn

	//搜寻某个元素
	cout << "[find5]" << *find(lst.begin(), lst.end(), 5) << endl;
	cout << "[find5]" << *find_if(lst.begin(), lst.end(), [](int i) {return i > 7; }) << endl;
	cout << "[find5]" << *find_if(lst.begin(), lst.end(), bind2nd(greater<int>(), 5)) << endl;
	cout << "[find5]" << *find_if_not(lst.begin(), lst.end(), not1(bind2nd(greater<int>(), 5))) << endl;

	//搜寻最后一个子区间
	str = "abcccdefghijklmnopqrklmstuvwxyz";
	substr = "klm";
	cout << "[klm]" << *find_end(str.begin(), str.end(), substr.begin(), substr.end()) << "[distance]" << distance(str.begin(), find_end(str.begin(), str.end(), substr.begin(), substr.end())) << endl;  //klm
	cout << "[klm]" << *find_end(str.begin(), str.end(), substr.begin(), substr.end(), [](char c1, char c2) {return c1 - 1 == c2; })        // lmn
		<< "[distance]" << distance(str.begin(), find_end(str.begin(), str.end(), substr.begin(), substr.end(), [](char c1, char c2) {return c1 - 1 == c2; })) << endl;
	cout << "[klm]" << *find_end(str.begin(), str.end(), substr.begin(), substr.end(), less<char>())        // jkl
		<< "[distance]" << distance(str.begin(), find_end(str.begin(), str.end(), substr.begin(), substr.end(), less<char>())) << endl;

	//搜寻某些元素第一次出现的地点
	cout << "[klm]" << *find_first_of(str.begin(), str.end(), substr.begin(), substr.end()) << "[distance]" << distance(str.begin(), find_first_of(str.begin(), str.end(), substr.begin(), substr.end())) << endl;  //klm
	cout << "[klm]" << *find_first_of(str.begin(), str.end(), substr.begin(), substr.end(), [](char c1, char c2) {return c1 - 1 == c2; })        // lmn
		<< "[distance]" << distance(str.begin(), find_first_of(str.begin(), str.end(), substr.begin(), substr.end(), [](char c1, char c2) {return c1 - 1 == c2; })) << endl;
	cout << "[klm]" << *find_first_of(str.begin(), str.end(), substr.begin(), substr.end(), less<char>())        // jkl
		<< "[distance]" << distance(str.begin(), find_first_of(str.begin(), str.end(), substr.begin(), substr.end(), less<char>())) << endl;

	//两个连续且相等的元素
	str = "abcddeg";
	cout << "[adjacent_find]"<< str << " " << *adjacent_find(str.begin(), str.end()) << endl;
	cout << "[adjacent_find]" << str << " " << *adjacent_find(str.begin(), str.end(), [](char c1, char c2) { return c1 + 2 == c2; }) << endl;

	//计算输入范围中每个元素与其前一元素之间的连续差值，并将结果输出到目标范围，或计算将差值运算替换为其他指定二元运算的一般化程序的结果。
	str = "aabbccdefg";
	string strtemp = "";
	vector<int> vctint;
	adjacent_difference(str.begin(), str.end(), back_inserter(vctint));
	cout << "[adjacent_difference]" << str << " " << strtemp << endl;
	str = "abcdddefg";
	strtemp = "";
	//vctint.clear();
	vector<int> vctint2;
	adjacent_difference(str.begin(), str.end(), back_inserter(vctint2), [](char c1, char c2) { return (int)(c2 - c1); });          //c1 为后一个 c2为前一个
	cout << "[adjacent_difference]" << str << " " << strtemp << endl;
}


void testSection()
{
	//区间相等
	string str = "abcdefgh123456";
	string str2 = "bcdefgh123456";
	string substr = "bcd";
	cout << "[equal]" << equal(substr.begin(), substr.end(), str.begin() + 2) << endl;
	cout << "[equal]" << equal(substr.begin(), substr.end(), str.begin() + 5, [](char c1, char c2) { return c1 < c2; }) << endl;

	{
		//区间第一处不同点
		string str = "abcdef";                                          // 字串小 目串大 first==end second!=end
		string substr = "abc";
		auto t1 = mismatch(substr.begin(), substr.end(), str.begin());  // 返回是个paire  first 是第一个区间的迭代器 second 是第二个
		cout << "[sart]" << distance(substr.begin(), t1.first) << "[end]" << (substr.end() == t1.first ? "true" : "false")       //当first为sunstr.end时 说明没有不匹配的情况 但并能说明两个相等 因为str可能更大
			<< "[end]" << distance(str.begin(), t1.second) << "[end]" << (str.end() == t1.second ? "true" : "false") << endl;    //second 为str.end时
	}

	{
		string str = "ab";                                            // 字串大 目串小 first!=end second==end
		string substr = "abc";
		auto t1 = mismatch(substr.begin(), substr.end(), str.begin());  // 返回是个paire  first 是第一个区间的迭代器 second 是第二个
		cout << "[sart]" << distance(substr.begin(), t1.first) << "[end]" << (substr.end() == t1.first ? "true" : "false")       //当first为sunstr.end时 说明没有不匹配的情况 但并能说明两个相等 因为str可能更大
			<< "[end]" << distance(str.begin(), t1.second) << "[end]" << (str.end() == t1.second ? "true" : "false") << endl;    //second 为str.end时
	}

	{
		string str = "abc";                                            // 字串 == 目串小 first==end second==end
		string substr = "abc";
		auto t1 = mismatch(substr.begin(), substr.end(), str.begin());  // 返回是个paire  first 是第一个区间的迭代器 second 是第二个
		cout << "[sart]" << distance(substr.begin(), t1.first) << "[end]" << (substr.end() == t1.first ? "true" : "false")       //当first为sunstr.end时 说明没有不匹配的情况 但并能说明两个相等 因为str可能更大
			<< "[end]" << distance(str.begin(), t1.second) << "[end]" << (str.end() == t1.second ? "true" : "false") << endl;    //second 为str.end时
	}

	{
		string str = "bcd";
		string substr = "abc";
		auto t1 = mismatch(substr.begin(), substr.end(), str.begin(), [](char c1, char c2) {return c1 + 1 == c2; });
		cout << "[sart]" << distance(substr.begin(), t1.first) << "[end]" << (substr.end() == t1.first ? "true" : "false")
			<< "[end]" << distance(str.begin(), t1.second) << "[end]" << (str.end() == t1.second ? "true" : "false") << endl;
	}

	{
		//检验 小于 字典序
		string str = "abcdef";    //false
		string substr = "abc";
		cout << "[<]" << lexicographical_compare(str.begin(), str.end(), substr.begin(), substr.end()) << endl;
	}

	{
		string str = "abbcdef";   //true
		string substr = "abc";
		cout << "[<]" << lexicographical_compare(str.begin(), str.end(), substr.begin(), substr.end()) << endl;
	}

	{
		string str = "abc";      //false
		string substr = "abc";
		cout << "[<]" << lexicographical_compare(str.begin(), str.end(), substr.begin(), substr.end()) << endl;
	}

	{
		string str = "ab";       //true
		string substr = "abc";
		cout << "[<]" << lexicographical_compare(str.begin(), str.end(), substr.begin(), substr.end()) << endl;
	}
}

void testModify()
{
	string str = "abcdef";
	string str2 = "";
	copy(str.begin(), str.end(), ostream_iterator<char>(cout, " "));   // 输出
	cout << endl;

	copy(str.begin(), str.end(), back_inserter(str2));                 // 插入
	cout << str2 << endl;

	*str2.begin() = 'A';
	cout << str2 << endl;
	copy(str.begin(), str.end(), str2.begin());                        // 覆盖
	cout << str2 << endl;

	list<int> lst1;
	list<int> lst2;
	list<int> lst3;

	for (int i = 1; i < 6; ++i)
	{
		lst1.push_back(i);
		lst2.push_back(i * i);
		cout << i << " ";
	}
	cout << endl;

	transform(lst1.begin(), lst1.end(), ostream_iterator<int>(cout, " "), negate<int>());
	cout << endl;
	transform(lst1.begin(), lst1.end(), lst2.begin(), ostream_iterator<int>(cout, " "), multiplies<int>());
	cout << endl;
}

void testNumber()
{
	list<int> lst;
	for (int i = 1; i < 6; ++i)
	{
		lst.push_back(i);
	}

	//和
	cout << "[accumulate 1-5]" << accumulate(lst.begin(), lst.end(), 0) << endl;  // 0 + 1 + 2 + 3 + 4 + 5;
	cout << "[accumulate 1-5]" << accumulate(lst.begin(), lst.end(), 0, [](int i, int j) {return i + j + 1; }) << endl;  //0 + 1 + 1 +   2 + 1 +   3 + 1 +   4 + 1 +   5 + 1;

	//内积
	cout << "[inner_product 1-5]" << inner_product(lst.begin(), lst.end(), lst.begin(), 0) << endl;  //1 * 1 +   2 * 2 +   3 * 3 +   4 * 4 +   5 * 5 = 55;
	// initValue = op1(initValue, op2(elem1, elem2))
	//  0 +    0 + (1 + 1 + 2) + 1   (2 + 2 + 2) + 1   +    (3 + 3 + 2) + 1   +    (4 + 4 + 2) + 1   +    (5 + 5 + 2)  + 1 = 45;
	//init     i    i   j   2    1	
	cout << "[inner_product 1-5]" << inner_product(lst.begin(), lst.end(), lst.begin(), 0, [](int i, int j) {return i + j + 1; }, [](int i, int j) {return i + j + 2; }) << endl;

	//部分和
	cout << "[partial_sum 1-5]";
	partial_sum(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "));  //a1; a1 + a2; a1 + a2 + a3; a1 + a2 + a3 + a4;
	cout << endl;

	cout << "[partial_sum 1-5]";
	//1 (1-2=2)2 (2-3=6)6 (6-4=24)24 (24-5=120)120
	//   i j      i j
	partial_sum(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "), [](int i, int j) { cout << "(" << i << "-" << j << "=" << i * j << ")";return i* j; });
	cout << endl;

	//差额和
	cout << "[adjacent_difference 1-5]";
	adjacent_difference(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "));  //a1; a2 - a1; a3 - a2; a4 - a3; a5 - a4;
	cout << endl;

	cout << "[adjacent_difference 1-5]";
	// 1 (2-1=2)2 (3-2=6)6 (4-3=12)12 (5-4=20)20
	//    j i      j i
	adjacent_difference(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "), [](int i, int j) { cout << "(" << i << "-" << j << "=" << i * j << ")"; return i * j; });
	cout << endl;
}

void testshareptr()
{
	shared_ptr<int> spi1;
	cout << "spi1:" << spi1.use_count() << endl;

	shared_ptr<int> spi2(new int(1));
	cout << "spi2:" << spi2.use_count() << endl;

	int* pi1 = new int(2);

	shared_ptr<int> spi3(pi1);
	cout << "spi3:" << spi3.use_count() << endl;

	spi3 = spi2;
	cout << "spi2:" << spi2.use_count() << endl;
	cout << "spi3:" << spi3.use_count() << endl;

	spi3.reset();
	cout << "spi2:" << spi2.use_count() << endl;
	cout << "spi3:" << spi3.use_count() << endl;

	cout << "-------------------------" << endl;

	{
		// 使用智能指针管理一块 int 型的堆内存
		shared_ptr<int> ptr1(new int(520));
		cout << "ptr1管理的内存引用计数: " << ptr1.use_count() << endl; // 1

		// 使用智能指针管理一块字符数组对应的堆内存
		shared_ptr<char> ptr2(new char[12]);
		cout << "ptr2管理的内存引用计数: " << ptr2.use_count() << endl; // 1

		// 创建智能指针对象, 不管理任何内存
		shared_ptr<int> ptr3;
		cout << "ptr3管理的内存引用计数: " << ptr3.use_count() << endl;// 0

		// 创建智能指针对象, 初始化为空
		shared_ptr<int> ptr4(nullptr);
		cout << "ptr4管理的内存引用计数: " << ptr4.use_count() << endl; // 0

		//如果智能指针被初始化了一块有效内存，那么这块内存的引用计数 + 1，
		//如果智能指针没有被初始化或者被初始化为 nullptr 空指针，引用计数不会 + 1。
		//另外，不要使用一个原始指针初始化多个 shared_ptr。
		//例如：
		//int* p = new int;
		//shared_ptr<int> p1(p);
		//shared_ptr<int> p2(p);		// error, 编译不会报错, 运行会出错
	}

	cout << "-------------------------" << endl;

	{
		//通过拷贝和移动构造函数初始化
		//当一个智能指针被初始化之后，就可以通过这个智能指针初始化其他新对象。
		//在创建新对象的时候，对应的拷贝构造函数或者移动构造函数就被自动调用了。

		// 使用智能指针管理一块 int 型的堆内存, 内部引用计数为 1
		shared_ptr<int> ptr1(new int(520));
		cout << "ptr1管理的内存引用计数: " << ptr1.use_count() << endl; //1

		//调用拷贝构造函数
		shared_ptr<int> ptr2(ptr1); //使用ptr1初始化新的智能指针对象
		cout << "ptr2管理的内存引用计数: " << ptr2.use_count() << endl; //2

		shared_ptr<int> ptr3 = ptr1;
		cout << "ptr3管理的内存引用计数: " << ptr3.use_count() << endl; //3

		//调用移动构造函数
		shared_ptr<int> ptr4(std::move(ptr1));
		cout << "ptr4管理的内存引用计数: " << ptr4.use_count() << "  ptr1管理的内存引用计数: " << ptr1.use_count() << endl; //3  0

		std::shared_ptr<int> ptr5 = std::move(ptr2);
		cout << "ptr5管理的内存引用计数: " << ptr5.use_count() << "  ptr2管理的内存引用计数: " << ptr2.use_count() << endl; //3  0

		//如果使用拷贝的方式初始化共享智能指针对象，这两个对象会同时管理同一块堆内存，堆内存对应的引用计数也会增加；
		//如果使用移动的方式初始智能指针对象，只是转让了内存的所有权，管理内存的对象并不会增加，因此内存的引用计数不会变化。
	}

	cout << "-------------------------" << endl;

	{
		//std::make_shared() 是模板函数。
		//template< class T, class... Args >
		//shared_ptr<T> make_shared(Args&&... args);
		//T：模板参数的数据类型
		//Args&&... args ：要初始化的数据，如果是通过 make_shared 创建对象，需按照构造函数的参数列表指定
		class Test
		{
		public:
			Test()
			{
				cout << "construct Test..." << endl;
			}
			Test(int x)
			{
				cout << "construct Test, x = " << x << endl;
			}
			Test(string str)
			{
				cout << "construct Test, str = " << str << endl;
			}
			~Test()
			{
				cout << "destruct Test ..." << endl;
			}
		};

		// 使用智能指针管理一块 int 型的堆内存, 内部引用计数为 1
		shared_ptr<int> ptr1 = make_shared<int>(520);
		cout << "ptr1管理的内存引用计数: " << ptr1.use_count() << endl;

		shared_ptr<Test> ptr2 = make_shared<Test>();
		cout << "ptr2管理的内存引用计数: " << ptr2.use_count() << endl;

		shared_ptr<Test> ptr3 = make_shared<Test>(520);
		cout << "ptr3管理的内存引用计数: " << ptr3.use_count() << endl;

		shared_ptr<Test> ptr4 = make_shared<Test>("我是要成为海贼王的男人!!!");
		cout << "ptr4管理的内存引用计数: " << ptr4.use_count() << endl;


		//ptr1管理的内存引用计数: 1
		//construct Test...
		//ptr2管理的内存引用计数 : 1
		//construct Test, x = 520
		//ptr3管理的内存引用计数 : 1
		//construct Test, str = 我是要成为海贼王的男人!!!
		//ptr4管理的内存引用计数 : 1
		//destruct Test ...
		//destruct Test ...
		//destruct Test ...
	}

	cout << "-------------------------" << endl;

	{
		// 使用智能指针管理一块 int 型的堆内存, 内部引用计数为 1
		shared_ptr<int> ptr1 = make_shared<int>(520);
		shared_ptr<int> ptr2 = ptr1;
		shared_ptr<int> ptr3 = ptr1;
		shared_ptr<int> ptr4 = ptr1;
		cout << "ptr1管理的内存引用计数: " << ptr1.use_count() << endl;    // 4
		cout << "ptr2管理的内存引用计数: " << ptr2.use_count() << endl;    // 4
		cout << "ptr3管理的内存引用计数: " << ptr3.use_count() << endl;    // 4
		cout << "ptr4管理的内存引用计数: " << ptr4.use_count() << endl;    // 4

		cout << endl << "after ptr4.reset();" << endl;
		ptr4.reset();
		cout << "ptr1管理的内存引用计数: " << ptr1.use_count() << endl;    // 3
		cout << "ptr2管理的内存引用计数: " << ptr2.use_count() << endl;    // 3
		cout << "ptr3管理的内存引用计数: " << ptr3.use_count() << endl;    // 3
		cout << "ptr4管理的内存引用计数: " << ptr4.use_count() << endl;    // 0

		shared_ptr<int> ptr5;
		ptr5.reset(new int(250));
		cout << "ptr5管理的内存引用计数: " << ptr5.use_count() << endl;    // 1

		shared_ptr<int> ptr6 = ptr1;		
		cout << "ptr6管理的内存引用计数: " << ptr6.use_count() << endl;    // 4
		ptr6.reset(new int(250));
		cout << "ptr6管理的内存引用计数: " << ptr6.use_count() << endl;    // 1

		//对于一个未初始化的共享智能指针，可以通过 reset 方法来初始化，当智能指针中有值的时候，调用 reset 会使引用计数减 1。
	}

	cout << "-------------------------" << endl;

	{
		//对基础数据类型来说，通过操作智能指针和操作智能指针管理的内存效果是一样的，可以直接完成数据的读写。
		//但是如果共享智能指针管理的是一个对象，那么就需要取出原始内存的地址再操作，可以调用共享智能指针类提供的 get() 方法得到原始地址，其函数原型如下：
		int len = 128;
		shared_ptr<char> ptr(new char[len]);
		// 得到指针的原始地址
		char* add = ptr.get();
		memset(add, 0, len);
		strcpy(add, "我是要成为海贼王的男人!!!");
		cout << "string: " << add << endl;             //string: 我是要成为海贼王的男人!!!

		shared_ptr<int> p(new int);
		*p = 100;
		cout << *p.get() << "  " << *p << endl;       //100  100
	}

	cout << "-------------------------" << endl;

	{
		//当智能指针管理的内存对应的引用计数变为 0 的时候，这块内存就会被智能指针析构掉了。
		//另外，我们在初始化智能指针的时候也可以自己指定删除动作，这个删除操作对应的函数被称之为删除器，
		//这个删除器函数本质是一个回调函数，我们只需要进行实现，其调用是由智能指针完成的。


		// 自定义删除器函数，释放int型内存
		//void deleteIntPtr(int* p)
		//{
		//	delete p;
		//	cout << "int 型内存被释放了...";
		//}
		//shared_ptr<int> ptr(new int(250), deleteIntPtr);
		shared_ptr<int> ptr2(new int(250), [](int* p) {delete p; }); //删除器函数也可以是 lambda 表达式
	}

}


unique_ptr<int> func()
{
	return unique_ptr<int>(new int(520));
}

void testuniqueptr()
{
	{
		//初始化
		//std::unique_ptr 是一个独占型的智能指针，它不允许其他的智能指针共享其内部的指针，可以通过它的构造函数初始化一个独占智能指针对象，但是不允许通过赋值将一个 unique_ptr 赋值给另一个 unique_ptr。
		//std::unique_ptr 不允许复制，但是可以通过函数返回给其他的 std::unique_ptr，还可以通过 std::move 来转译给其他的 std::unique_ptr，这样原始指针的所有权就被转移了，这个原始指针还是被独占的。

		// 通过构造函数初始化
		unique_ptr<int> ptr1(new int(10));
		// 通过转移所有权的方式初始化
		unique_ptr<int> ptr2 = move(ptr1);
		unique_ptr<int> ptr3 = func();

		ptr1.reset();    //使用 reset 方法可以让 unique_ptr 解除对原始内存的管理
		ptr2.reset(new int(250)); //重新指定智能指针管理的原始内存

		//如果想要获取独占智能指针管理的原始地址，可以调用 get () 方法
		cout << *ptr2.get() << endl;	// 得到内存地址中存储的实际数值 250
	}

	{
		//删除器
		//unique_ptr 指定删除器和 shared_ptr 指定删除器是有区别的，unique_ptr 指定删除器的时候需要确定删除器的类型，所以不能像 shared_ptr 那样直接指定删除器。
		shared_ptr<int> ptr1(new int(10), [](int* p) {delete p; });	// ok
		//unique_ptr<int> ptr1(new int(10), [](int* p) {delete p; });	// error

		using func_ptr = void(*)(int*);
		// func_ptr 的类型和 lambda表达式的类型是一致的
		unique_ptr<int, func_ptr> ptr2(new int(10), [](int* p) {delete p; });

		//在 lambda 表达式没有捕获任何变量的情况下是正确的，如果捕获了变量，编译时则会报错。
		//在 lambda 表达式没有捕获任何外部变量时，可以直接转换为函数指针，一旦捕获了就无法转换了，如果想要让编译器成功通过编译，那么需要使用可调用对象包装器来处理声明的函数指针：
		using func_ptr = void(*)(int*);
		unique_ptr<int, function<void(int*)>> ptr3(new int(10), [&](int* p) {delete p; });
	}
}

void testweakptr()
{
	//弱引用智能指针 std::weak_ptr 可以看做是 shared_ptr 的助手，它不管理 shared_ptr 内部的指针。
	//std::weak_ptr 没有重载操作符* 和->，因为它不共享指针，不能操作资源，所以它的构造不会增加引用计数，析构也不会减少引用计数，
	//它的主要作用就是作为一个旁观者监视 shared_ptr 中管理的资源是否存在。

	{
		//初始化
		//// 默认构造函数
		//constexpr weak_ptr() noexcept;

		//// 拷贝构造
		//weak_ptr(const weak_ptr & x) noexcept;

		//template <class U>
		//weak_ptr(const weak_ptr<U>&x) noexcept;

		//// 通过shared_ptr对象构造
		//template <class U>
		//weak_ptr(const shared_ptr<U>&x) noexcept;

		shared_ptr<int> sp(new int);

		weak_ptr<int> wp1;         //造了一个空 weak_ptr 对象
		weak_ptr<int> wp2(wp1);    //通过一个空 weak_ptr 对象构造了另一个空 weak_ptr 对象
		weak_ptr<int> wp3(sp);     //通过一个 shared_ptr 对象构造了一个可用的 weak_ptr 实例对象
		weak_ptr<int> wp4;
		wp4 = sp;                  //通过一个 shared_ptr 对象构造了一个可用的 weak_ptr 实例对象（这是一个隐式类型转换）
		weak_ptr<int> wp5;
		wp5 = wp3;                 //通过一个 weak_ptr 对象构造了一个可用的 weak_ptr 实例对象
	}

	{
		//常用方法
		//use_count()
		//通过调用 std::weak_ptr 类提供的 use_count() 方法可以获得当前所观测资源的引用计数。

		//expired()
		//判断观测的资源是否已经被释放。

		// 返回true表示资源已经被释放, 返回false表示资源没有被释放
		//bool expired() const noexcept;
		//lock()
		//通过调用 std::weak_ptr 类提供的 lock() 方法来获取管理所监测资源的 shared_ptr 对象，函数原型如下：
		//shared_ptr<element_type> lock() const noexcept;

		shared_ptr<int> sp1, sp2;
		weak_ptr<int> wp;

		sp1 = std::make_shared<int>(520);
		wp = sp1;

		//通过调用 lock() 方法,得到一个用于管理 weak_ptr 对象所监测的资源的 共享智能指针对象,
		//使用这个对象初始化 sp2，此时所监测资源的引用计数为 2
		sp2 = wp.lock();
		cout << "use_count: " << wp.use_count() << endl; //2

		sp1.reset(); //共享智能指针 sp1 被重置，weak_ptr 对象所监测的资源的引用计数减 1
		cout << "use_count: " << wp.use_count() << endl; //1

		//sp1 重新被初始化，并且管理的还是 weak_ptr 对象所监测的资源，因此引用计数加 1
		sp1 = wp.lock();
		cout << "use_count: " << wp.use_count() << endl; //2

		//共享智能指针对象 sp1 和 sp2 管理的是同一块内存，因此最终打印的内存中的结果是相同的，都是 520
		cout << "*sp1: " << *sp1 << endl; //520
		cout << "*sp2: " << *sp2 << endl; //520


		//reset()
		//清空对象，使其不监测任何资源。
		//返回管理 this 的 shared_ptr
		//如果在一个类中编写了一个函数，通过这个函数，得到管理当前对象的共享智能指针，我们可能会写出如下代码：

		struct Test
		{
			shared_ptr<Test> getSharedPtr()
			{
				return shared_ptr<Test>(this);
			}

			~Test()
			{
				cout << "class Test is disstruct ..." << endl;
			}

		};

		{
			shared_ptr<Test> sp1(new Test);
			cout << "use_count: " << sp1.use_count() << endl;
			shared_ptr<Test> sp2 = sp1->getSharedPtr();
			cout << "use_count: " << sp1.use_count() << endl;
		}
		//use_count: 1
		//use_count : 1
		//class Test is disstruct ...
		//class Test is disstruct ...


		//通过输出的结果可以看到一个对象被析构了两次，其原因是这样的：在这个例子中使用同一个指针 this 构造了两个智能指针对象 sp1 和 sp2，
		//这二者之间是没有任何关系的，因为 sp2 并不是通过 sp1 初始化得到的实例对象，在离开作用域之后 this 将被构造的两个智能指针各自析构，导致重复析构的错误。

		
		
		//这个问题可以通过 weak_ptr 来解决，通过 wek_ptr 返回管理 this 资源的共享智能指针对象 shared_ptr。
		//C++11 中为我们提供了一个模板类叫做 std::enable_shared_from_this<T>，这个类中有一个方法叫做 shared_from_this()，
		//通过这个方法可以返回一个共享智能指针，在函数的内部就是使用 weak_ptr 来监测 this 对象，并通过调用 weak_ptr 的 lock() 方法返回一个 shared_ptr 对象。		
		{
			struct Test : public enable_shared_from_this<Test>
			{
				shared_ptr<Test> getSharedPtr()
				{
					return shared_from_this();
				}
				~Test()
				{
					cout << "class Test is disstruct ..." << endl;
				}
			};

			shared_ptr<Test> sp1(new Test);
			cout << "use_count: " << sp1.use_count() << endl;
			shared_ptr<Test> sp2 = sp1->getSharedPtr();
			cout << "use_count: " << sp1.use_count() << endl;

			//use_count: 1
			//use_count: 2
			//class Test is disstruct ...
			//最后需要强调一个细节：在调用 enable_shared_from_this 类的 shared_from_this() 方法之前，必须要先初始化函数内部 weak_ptr 对象，
			//否则该函数无法返回一个有效的 shared_ptr 对象（具体处理方法可以参考上面的示例代码）。
		}




		//解决循环引用问题
		//智能指针如果循环引用会导致内存泄露：

		{
			struct TA;
			struct TB;

			struct TA
			{
				shared_ptr<TB> bptr;
				~TA()
				{
					cout << "class TA is disstruct ..." << endl;
				}
			};

			struct TB
			{
				shared_ptr<TA> aptr;
				~TB()
				{
					cout << "class TB is disstruct ..." << endl;
				}
			};

			shared_ptr<TA> ap(new TA);
			shared_ptr<TB> bp(new TB);
			cout << "TA object use_count: " << ap.use_count() << endl;
			cout << "TB object use_count: " << bp.use_count() << endl;

			ap->bptr = bp;
			bp->aptr = ap;
			cout << "TA object use_count: " << ap.use_count() << endl;
			cout << "TB object use_count: " << bp.use_count() << endl;


			//TA object use_count : 1
			//TB object use_count : 1
			//TA object use_count : 2
			//TB object use_count : 2
		}
		
		//在测试程序中，共享智能指针 ap、bp 对 TA、TB 实例对象的引用计数变为 2，在共享智能指针离开作用域之后引用计数只能减为1，这种情况下不会去删除智能指针管理的内存，
		//导致类 TA、TB 的实例对象不能被析构，最终造成内存泄露。通过使用 weak_ptr 可以解决这个问题，只要将类 TA 或者 TB 的任意一个成员改为 weak_ptr：

		{
			struct TA;
			struct TB;

			struct TA
			{
				weak_ptr<TB> bptr;
				~TA()
				{
					cout << "class TA is disstruct ..." << endl;
				}
			};

			struct TB
			{
				shared_ptr<TA> aptr;
				~TB()
				{
					cout << "class TB is disstruct ..." << endl;
				}
			};

			shared_ptr<TA> ap(new TA);
			shared_ptr<TB> bp(new TB);
			cout << "TA object use_count: " << ap.use_count() << endl;
			cout << "TB object use_count: " << bp.use_count() << endl;

			ap->bptr = bp;
			bp->aptr = ap;
			cout << "TA object use_count: " << ap.use_count() << endl;
			cout << "TB object use_count: " << bp.use_count() << endl;

			//TA object use_count : 1
			//TB object use_count : 1
			//TA object use_count : 2
			//TB object use_count : 1
			//class TB is disstruct ...
			//class TA is disstruct ...

			//上面程序中，在对类 TA 成员赋值时 ap->bptr = bp; 由于 bptr 是 weak_ptr 类型，这个赋值操作并不会增加引用计数，所以 bp 的引用计数仍然为 1，在离开作用域之后 bp 的引用计数减为 0，类 TB 的实例对象被析构。
			//在类 TB 的实例对象被析构的时候，内部的 aptr 也被析构，其对 TA 对象的管理解除，内存的引用计数减为 1，当共享智能指针 ap 离开作用域之后，对 TA 对象的管理也解除了，内存的引用计数减为 0，类 TA 的实例对象被析构。
		}
	}

}



// Durations
// #include <ratio>
// #include <chrono>
void testtime1()
{
	//chrono 是一个time library, 源于boost，现在已经是C++标准。话说今年似乎又要出新标准了，好期待啊！
	//要使用chrono库，需要#include<chrono>，其所有实现均在std::chrono namespace下。
	//注意标准库里面的每个命名空间代表了一个独立的概念。所以下文中的概念均以命名空间的名字表示！ 
	//chrono是一个模版库，使用简单，功能强大，只需要理解三个概念：duration、time_point、clock
	//
	//	1.Durations
	//	std::chrono::duration 表示一段时间，比如两个小时，12.88秒，半个时辰，一炷香的时间等等，只要能换算成秒即可。
	//	template <class Rep, class Period = ratio<1> > class duration;
	//其中
	//	Rep表示一种数值类型，用来表示Period的数量，比如int float double
	//	Period是ratio类型，用来表示【用秒表示的时间单位】比如second milisecond
	//	常用的duration<Rep, Period>已经定义好了，在std::chrono::duration下：
	//	ratio<3600, 1>                  hours
	//	ratio<60, 1>                    minutes
	//	ratio<1, 1>                     seconds
	//	ratio<1, 1000>                  milisecond
	//	ratio<1, 1000000>               microsecond
	//	ratio<1, 1000000000>            nanosecon
	//
	//	这里需要说明一下ratio这个类模版的原型：
	//	template <intmax_t N, intmax_t D = 1> class ratio;
	//  N代表分子，D代表分母，所以ratio表示一个分数值。
	//	注意，我们自己可以定义Period，比如ratio<1, -2>表示单位时间是 - 0.5秒。
	//
	//	由于各种duration表示不同，chrono库提供了duration_cast类型转换函数。
	//	template < class ToDuration, class Rep, class Period>
	//	constexpr ToDuration duration_cast(const duration<Rep, Period>&dtn);
	//
	//典型的用法是表示一段时间：

	typedef std::chrono::duration<int> seconds_type;
	typedef std::chrono::duration<int, std::milli> milliseconds_type;
	typedef std::chrono::duration<int, std::ratio<60 * 60>> hours_type;
	
	{
		hours_type h_oneday(24);                      // 24h
		seconds_type s_oneday(60 * 60 * 24);          // 86400s
		milliseconds_type ms_oneday(s_oneday);        // 86400000ms

		cout << h_oneday.count() << " h_oneday " << endl;
		cout << s_oneday.count() << " s_oneday " << endl;
		cout << ms_oneday.count() << " ms_oneday " << endl;
	}

	{
		seconds_type s_onehour(60 * 60);              // 3600s
		//hours_type h_onehour(s_onehour);             // NOT VALID (type truncates)   格式错误 应用下面方式
		hours_type h_onehour(std::chrono::duration_cast<hours_type>(s_onehour));
		milliseconds_type ms_onehour(s_onehour);      // 3600000ms (ok, no type truncation)

		cout << s_onehour.count() << " s_onehour" << endl;
		cout << h_onehour.count() << " h_onehour" << endl;
		cout << ms_onehour.count() << " ms_onehour" << endl;
	}	

	// duration还有一个成员函数count()返回Rep类型的Period数量	
	{
		using namespace std::chrono;
		// std::chrono::milliseconds is an instatiation of std::chrono::duration:
		milliseconds foo(1000); // 1 second
		foo *= 60;

		cout << "duration (in periods): " << foo.count() << " milliseconds" << endl;

		cout << "duration (in seconds): " << foo.count() * milliseconds::period::num / milliseconds::period::den << " seconds"
			<< "[milliseconds::period::num]" << milliseconds::period::num << "[milliseconds::period::den]" << milliseconds::period::den << endl;


		// 自定义时间
		using myratio = ratio<3,7>;
		using mysec = duration<long long, myratio>;

		mysec ms(100);
		cout << "[mysec]" << ms.count() << endl;
		cout << "[seconds]" << ms.count() * mysec::period::num / mysec::period::den
			<<"[mysec::period::num]" << mysec::period::num << "[mysec::period::den]" << mysec::period::den << endl;
		
	}
	return;
}

// Time points
// #include <chrono>
// #include <ctime>
void testtime2()
{
	//Time points
	//std::chrono::time_point 表示一个具体时间，如上个世纪80年代、你的生日、今天下午、火车出发时间等，只要它能用计算机时钟表示。
	//鉴于我们使用时间的情景不同，这个time point 具体到什么程度，由选用的单位决定。
	//一个time point 必须有一个clock计时。参见clock的说明。
	//
	// template <class Clock, class Duration = typename Clock::duration>  class time_point;

	using namespace std::chrono;	
	system_clock::time_point tp_epoch;    // epoch value
	cout << "1 second since tp_epoch = " << tp_epoch.time_since_epoch().count() << " system_clock periods" << endl;
	
	time_point <system_clock, duration<int>> tp_seconds(duration<int>(1));	
	system_clock::time_point tp(tp_seconds);
	
	cout << "1 second since system_clock epoch = " << tp.time_since_epoch().count() << " system_clock periods" << endl;
	
	// display time_point:
	time_t tt = system_clock::to_time_t(tp);
	cout << "time_point tp is: " << ctime(&tt);


	//time_point有一个函数time_from_eproch()用来获得1970年1月1日到time_point时间经过的duration。
	//举个例子，如果timepoint以天为单位，函数返回的duration就以天为单位。
	//
	//由于各种time_point表示方式不同，chrono也提供了相应的转换函数 time_point_cast。
	//template < class ToDuration, class Clock, class Duration>
	//time_point<Clock, ToDuration> time_point_cast(const time_point<Clock, Duration>&tp);

	{
		using namespace std::chrono;
		typedef duration<int, std::ratio<60 * 60 * 24>> days_type;
		time_point<system_clock, days_type> today = time_point_cast<days_type>(system_clock::now());
		cout << today.time_since_epoch().count() << " days since epoch" << endl;
	}

	{
		// 自定义
		time_point <system_clock, duration<int>> tp_seconds(duration<int>(1));
		system_clock::time_point tp1;
		system_clock::time_point tp2;
		tp1 = system_clock::from_time_t(111);
		tp2 = system_clock::from_time_t(222);

		//class std::chrono::duration<__int64,struct std::ratio<1,10000000> >
		using mydur = std::chrono::duration<__int64, struct std::ratio<1, 10000000> >;
		auto itt = tp2 - tp1;
		//typename ttt = typeid(itt);
		mydur myd;
		//using period = typename itt; itt.
		cout << "[tp2-tp1]" << endl
			<< "         [default]" <<(tp2 - tp1).count() << endl
			<< "         [double]" << duration_cast<duration<double>>(tp2 - tp1).count() << endl
			<< "         [int]" << duration_cast<duration<int>>(tp2 - tp1).count() << endl
			<< "         [typeid]" << typeid(itt).name() << endl
			<< "         [den]" << mydur::period::den << endl;
		cout << "[tp2-tp1]" << (tp2 - tp1).count() << "[itt_mat]" << itt.max().count() << "[itt_min]" << itt.min().count() << endl;
		//cout << "[tp2-tp1]" << (tp2 - tp1).count() << "[itt]" << typeid(itt).name() << "[itt]" << itt.period::den << endl;
		//cout << "[tp2-tp1]" << (tp2 - tp1).count() << "[itt]" << typeid(itt).name() << "[itt]" << myd.period::den << endl;
	}
}

// Clocks
// #include <ctime>
// #include <ratio>
// #include <chrono>
void testtime3()
{
	//3.Clocks
	//
	//std::chrono::system_clock 它表示当前的系统时钟，系统中运行的所有进程使用now()得到的时间是一致的。
	//每一个clock类中都有确定的time_point, duration, Rep, Period 类型。
	//操作有：
	//now() 当前时间time_point
	//to_time_t() time_point转换成time_t秒
	//from_time_t() 从time_t转换成time_point
	//典型的应用是计算时间日期：

	using std::chrono::system_clock;	
	std::chrono::duration<int, std::ratio<60 * 60 * 24> > one_day(1);	
	system_clock::time_point today = system_clock::now();
	system_clock::time_point tomorrow = today + one_day;	
	std::time_t tt;	
	tt = system_clock::to_time_t(today);
	std::cout << "today is: " << ctime(&tt);	
	tt = system_clock::to_time_t(tomorrow);
	std::cout << "tomorrow will be: " << ctime(&tt);


	//具体来说，时钟类 system_clock 是一个系统范围的实时时钟。
	// system_clock 提供了对当前时间点 time_point 的访问，将得到时间点转换为 time_t 类型的时间对象，
	// 就可以基于这个时间对象获取到当前的时间信息了。
	//struct system_clock { // wraps GetSystemTimePreciseAsFileTime/GetSystemTimeAsFileTime
	//	using rep = long long;
	//	using period = ratio<1, 10'000'000>; // 100 nanoseconds
	//	using duration = chrono::duration<rep, period>;
	//	using time_point = chrono::time_point<system_clock>;
	//	static constexpr bool is_steady = false;

	//	_NODISCARD static time_point now() noexcept
	//	{ // get current time
	//		return time_point(duration(_Xtime_get_ticks()));
	//	}

	//	_NODISCARD static __time64_t to_time_t(const time_point& _Time) noexcept
	//	{ // convert to __time64_t
	//		return duration_cast<seconds>(_Time.time_since_epoch()).count();
	//	}

	//	_NODISCARD static time_point from_time_t(__time64_t _Tm) noexcept
	//	{ // convert from __time64_t
	//		return time_point{ seconds{_Tm} };
	//	}
	//};
	// 
	//通过以上源码可以了解到在 system_clock 类中的一些细节信息：
	//	rep：时钟周期次数是通过整形来记录的 long long
	//	period：一个时钟周期是 100 纳秒 ratio<1, 10'000'000>
	//	duration：时间间隔为 rep * period 纳秒 chrono::duration<rep, period>
	//	time_point：时间点通过系统时钟做了初始化 chrono::time_p - oint<system_clock>，里面记录了新纪元时间点
	//
	//提供了三个静态成员函数：
	//// 返回表示当前时间的时间点。
	//	static std::chrono::time_point<std::chrono::system_clock> now() noexcept;
	//	// 将 time_point 时间点类型转换为 std::time_t 类型
	//	static std::time_t to_time_t(const time_point & t) noexcept;
	//	// 将 std::time_t 类型转换为 time_point 时间点类型
	//	static std::chrono::system_clock::time_point from_time_t(std::time_t t) noexcept;
	{
		using namespace std::chrono;
		// 新纪元1970.1.1时间
		system_clock::time_point epoch;

		duration<int, ratio<60 * 60 * 24>> day(1);
		// 新纪元1970.1.1时间 + 1天
		system_clock::time_point ppt(day);

		using dday = duration<int, ratio<60 * 60 * 24>>;
		// 新纪元1970.1.1时间 + 10天
		time_point<system_clock, dday> t(dday(10));

		// 系统当前时间
		system_clock::time_point today = system_clock::now();

		// 转换为time_t时间类型
		time_t tm = system_clock::to_time_t(today);
		cout << "今天的日期是:    " << ctime(&tm);

		time_t tm1 = system_clock::to_time_t(today + day);
		cout << "明天的日期是:    " << ctime(&tm1);

		time_t tm2 = system_clock::to_time_t(epoch);
		cout << "新纪元时间:      " << ctime(&tm2);

		time_t tm3 = system_clock::to_time_t(ppt);
		cout << "新纪元时间+1天:  " << ctime(&tm3);

		time_t tm4 = system_clock::to_time_t(t);
		cout << "新纪元时间+10天: " << ctime(&tm4);
	}




	//std::chrono::steady_clock 为了表示稳定的时间间隔，后一次调用now()得到的时间总是比前一次的值大
	// （这句话的意思其实是，如果中途修改了系统时间，也不影响now()的结果），每次tick都保证过了稳定的时间间隔。
	//操作有：
	//now() 获取当前时钟
	//典型的应用是给算法计时：	

	using namespace std::chrono;	
	steady_clock::time_point t1 = steady_clock::now();	
	std::cout << "printing out 1000 stars...\n";
	for (int i = 0; i < 1000; ++i) std::cout << "*";
	std::cout << std::endl;
	
	steady_clock::time_point t2 = steady_clock::now();	
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);	
	std::cout << "It took me " << time_span.count() << " seconds.";
	std::cout << std::endl;


	//如果我们通过时钟不是为了获取当前的系统时间，而是进行程序耗时的时长，
	// 此时使用 syetem_clock 就不合适了，因为这个时间可以跟随系统的设置发生变化。
	// 在 C++11 中提供的时钟类 steady_clock 相当于秒表，只要启动就会进行时间的累加，
	// 并且不能被修改，非常适合于进行耗时的统计。
	//
	//struct steady_clock { // wraps QueryPerformanceCounter
	//	using rep = long long;
	//	using period = nano;
	//	using duration = nanoseconds;
	//	using time_point = chrono::time_point<steady_clock>;
	//	static constexpr bool is_steady = true;
	//
	//	// get current time
	//	_NODISCARD static time_point now() noexcept
	//	{
	//		// doesn't change after system boot
	//		const long long _Freq = _Query_perf_frequency();
	//		const long long _Ctr = _Query_perf_counter();
	//		static_assert(period::num == 1, "This assumes period::num == 1.");
	//		const long long _Whole = (_Ctr / _Freq) * period::den;
	//		const long long _Part = (_Ctr % _Freq) * period::den / _Freq;
	//		return time_point(duration(_Whole + _Part));
	//	}
	//};
	//通过以上源码可以了解到在 steady_clock 类中的一些细节信息：
	//
	//rep：时钟周期次数是通过整形来记录的 long long
	//period：一个时钟周期是 1 纳秒 nano
	//duration：时间间隔为 1 纳秒 nanoseconds
	//time_point：时间点通过系统时钟做了初始化 chrono::time_point<steady_clock>
	//另外，在这个类中也提供了一个静态的 now() 方法，用于得到当前的时间点，函数原型如下：
	//
	//static std::chrono::time_point<std::chrono::steady_clock> now() noexcept;

	//假设要测试某一段程序的执行效率，可以计算它执行期间消耗的总时长
	{
		// 获取开始时间点
		steady_clock::time_point start = steady_clock::now();
		// 执行业务流程
		cout << "print 1000 stars ...." << endl;
		for (int i = 0; i < 1000; ++i)
		{
			cout << "*";
		}
		cout << endl;
		// 获取结束时间点
		steady_clock::time_point last = steady_clock::now();
		// 计算差值
		auto dt = last - start;
		cout << "总共耗时: " << dt.count() << "纳秒" << endl;
	}


	//最后一个时钟，std::chrono::high_resolution_clock 顾名思义，这是系统可用的最高精度的时钟。
	//实际上high_resolution_clock只不过是system_clock或者steady_clock的typedef。
	//操作有：
	//now() 获取当前时钟。
}

#include <ctime>
#include <iomanip>
#include <sstream>
void f4()
{
	cout << "print 1000 stars ...." << endl;
	for (int i = 0; i < 1000; ++i)
	{
		cout << "*";
	}
	cout << endl;
}
using namespace std;
using Clock = chrono::high_resolution_clock;
using Ms = chrono::milliseconds;
using Sec = chrono::seconds;
template<class Duration>
using TimePoint = chrono::time_point<Clock, Duration>;

void print_ms(const TimePoint<Ms>& time_point)
{
	std::cout << time_point.time_since_epoch().count() << " ms\n";
}
void testtime4()
{
	using namespace std::chrono;

	//duration_cast
	//duration_cast 是 chrono 库提供的一个模板函数，这个函数不属于 duration 类。
	// 通过这个函数可以对 duration 类对象内部的时钟周期 Period，和周期次数的类型 Rep 进行修改，该函数原型如下：
	//
	//	template <class ToDuration, class Rep, class Period>
	//constexpr ToDuration duration_cast(const duration<Rep, Period>&dtn);
	//在源周期能准确地为目标周期所整除的场合（例如小时到分钟），
	//浮点时长和整数时长间转型能隐式进行无需使用 duration_cast ，其他情况下都需要通过函数进行转换。
	//
	//	我们可以修改一下上面测试程序执行时间的代码，在代码中修改 duration 对象的属性：
	{
		auto t1 = steady_clock::now();
		f4();
		auto t2 = steady_clock::now();

		// 整数时长：要求 duration_cast
		auto int_ms = duration_cast<chrono::milliseconds>(t2 - t1);

		// 小数时长：不要求 duration_cast
		duration<double, ratio<1, 1000>> fp_ms = t2 - t1;

		cout << "f4() took " << fp_ms.count() << " ms, "
			<< "or " << int_ms.count() << " whole milliseconds\n";

		//print 1000 stars ....
		//	* ***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************
		//	f() took 40.2547 ms, or 40 whole milliseconds
	}

	//time_point_cast
	//time_point_cast 也是 chrono 库提供的一个模板函数，这个函数不属于 time_point 类。
	// 函数的作用是对时间点进行转换，因为不同的时间点对象内部的时钟周期 Period，和周期次数的类型 Rep 可能也是不同的，
	// 一般情况下它们之间可以进行隐式类型转换，也可以通过该函数显示的进行转换，函数原型如下：
	//
	//	template <class ToDuration, class Clock, class Duration>
	//time_point<Clock, ToDuration> time_point_cast(const time_point<Clock, Duration> &t);
	//关于函数的使用，示例代码如下：
	{
		TimePoint<Sec> time_point_sec(Sec(6));
		// 无精度损失, 可以进行隐式类型转换
		TimePoint<Ms> time_point_ms(time_point_sec);
		print_ms(time_point_ms);    // 6000 ms

		time_point_ms = TimePoint<Ms>(Ms(6789));
		// error，会损失精度，不允许进行隐式的类型转换
		//TimePoint<Sec> sec(time_point_ms);

		// 显示类型转换,会损失精度。6789 truncated to 6000
		time_point_sec = std::chrono::time_point_cast<Sec>(time_point_ms);
		print_ms(time_point_sec); // 6000 ms

		//注意事项：关于时间点的转换如果没有没有精度的损失可以直接进行隐式类型转换，
		//如果会损失精度只能通过显示类型转换，也就是调用 time_point_cast 函数来完成该操作。
	}


	//微软的实现是这样的：
	//	namespace std
	//{
	//	namespace chrono
	//	{
	//		struct system_clock
	//		{
	//			static time_point now() __NOEXCEPT
	//			{
	//				return (time_point(duration(_Xtime_get_ticks())));
	//			}
	//			_Xtime_get_ticks（）使用GetSystemTimeAsFileTime（） 。 该功能的精度为1毫秒。

	//需要高精度时间戳（绝对时间点），而不是计算相对时间，那么可以考虑这个API:

	//GetSystemTimeAsFileTime()
	//	该函数返回自1601年1月1日起，到现在的时间（以 100ns 为单位）。
	//	其实，Windows上的 std::clock() 函数就是通过 GetSystemTimeAsFileTime() 来实现的，
	//  只不过 std::clock() 返回的是从程序启动到当前的时间（毫秒数），如下：
	//
	//	clock_t __cdecl clock(
	//		void
	//	)
	//{
	//	unsigned __int64 current_tics;
	//	FILETIME ct;
	//	GetSystemTimeAsFileTime(&ct);
	//	current_tics = (unsigned __int64)ct.dwLowDateTime +
	//		(((unsigned __int64)ct.dwHighDateTime) << 32);
	//	/* calculate the elapsed number of 100 nanosecond units */
	//	current_tics -= start_tics;  // start_tics 在程序启动时初始化
	//	/* return number of elapsed milliseconds */
	//	return (clock_t)(current_tics / 10000);
	//}
	//
	//想要获得从1601年1月1日以来，到目前为止所经历过的 微秒(micro seconds)数，可以这样做：
	//FILETIME fileTime;
	//long long now_long;
	//GetSystemTimeAsFileTime(&fileTime);
	//now_long = (long long(fileTime.dwHighDateTime) << 32) + fileTime.dwLowDateTime;
	//std::cout << "micro time from 1601.1.1:00:00:00 is: " << (now_long / 10) << std::endl;


	// default_value
	time_point<system_clock> startTime;// 1970-1-1 8:0:0;
	std::time_t tmStartTime = system_clock::to_time_t(startTime);
	std::cout << "startTime_time_t " << tmStartTime <<  " startTime_put_time " << std::put_time(std::localtime(&tmStartTime), "%F %T") << std::endl;
	//startTime_time_t 0 startTime_put_time 1970-01-01 08:00:00
	

	// get current time
	time_point<system_clock> nowTime = system_clock::now();
	std::time_t tmNowTime = system_clock::to_time_t(nowTime);
	std::cout << "nowTime_time_t " << tmNowTime << " nowTime_str " << std::put_time(std::localtime(&tmNowTime), "%F %T") << std::endl;
	//nowTime_time_t 1661218579 nowTime_str 2022 - 08 - 23 09:36 : 19	


	// use timestamp
	// 2020-01-08 15:05:50(1578466970)
	time_point<system_clock> stampTime(seconds(1578466970));
	std::time_t tmStampTime = system_clock::to_time_t(stampTime);
	std::cout << "stampTime_time_t " << tmStampTime << " stampTime_str " << std::put_time(std::localtime(&tmStampTime), "%F %T") << std::endl;
	//stampTime_time_t 1578466970 stampTime_str 2020 - 01 - 08 15:02 : 50	


	// some hours ago
	std::time_t tmSomeTimeAgo = system_clock::to_time_t(nowTime - hours(22) - minutes(30));
	std::cout << "22 hours 30 minutes ago time_t" << tmSomeTimeAgo << "22 hours 30 minutes ago " << std::put_time(std::localtime(&tmSomeTimeAgo), "%F %T") << std::endl;
	//22 hours 30 minutes ago time_t166113757922 hours 30 minutes ago 2022 - 08 - 22 11:06 : 19	


	// get time from string
	// use "std::get_time()"
	std::tm aTime;
	std::string strTime("2008-08-08 10:0:0");
	std::stringstream ssTime(strTime);
	ssTime.imbue(std::locale("de_DE.utf-8"));
	ssTime >> std::get_time(&aTime, "%Y-%m-%d %H:%M:%S");
	time_point<system_clock> tp = system_clock::from_time_t(std::mktime(&aTime));
	std::time_t aTestTime = system_clock::to_time_t(tp);
	std::cout << "aTime_time_t " << aTestTime << " aTime_str " << std::put_time(std::localtime(&aTestTime), "%F %T") << std::endl;
	std::cout << "compare: nowTime >= aTime ? " << (nowTime >= tp ? "true" : "false") << std::endl;
	//aTime_time_t 1218160800 aTime_str 2008 - 08 - 08 10:00 : 00
	//compare: nowTime >= aTime ? true


	// end time
	time_point<system_clock> endTime = system_clock::now();
	std::time_t tmEndTime = system_clock::to_time_t(endTime);
	std::cout << "endTime_time_t " << tmEndTime << " endTime_str " << std::put_time(std::localtime(&tmEndTime), "%F %T") << std::endl;
	std::cout << "the program used\t" << duration_cast<microseconds>(endTime - nowTime).count() << "us.\n";
	//endTime_time_t 1661218579 endTime_str 2022 - 08 - 23 09:36 : 19
	//the program used        16584us.


	// used time
	time_point<system_clock> p1 = system_clock::now();   // 默认时间间隔为 100纳秒 也就是1后7个0
	std::time_t tmNowTime1 = system_clock::to_time_t(p1);
	cout << "1  " << p1.time_since_epoch().count() << " time_t " << tmNowTime1 << endl;
	time_point<steady_clock> p3 = steady_clock::now();     // 默认时间间隔为 1纳秒 也就是1后9个0
	cout << "3  " << p3.time_since_epoch().count() << endl;
	this_thread::sleep_for(milliseconds(1234));
	this_thread::sleep_for(seconds(1));
	time_point<system_clock> p2 = system_clock::now();
	std::time_t tmNowTime2 = system_clock::to_time_t(p2);
	cout << "2  " << p2.time_since_epoch().count() << " time_t " << tmNowTime2 << endl;

	time_point<steady_clock> p4 = steady_clock::now();
	cout << "4  " << p4.time_since_epoch().count() << " used " << p4.time_since_epoch().count() - p3.time_since_epoch().count() << endl;

	std::cout << "[timeuse_defalut]" << (p2 - p1).count()
		<< "[timeuse_s]" << duration_cast<duration<int, std::ratio<1, 1>>>(p2 - p1).count()
		<< "[timeuse_milis]" << duration_cast<duration<int, std::ratio<1, 1000>>>(p2 - p1).count()
		<< "[timeuse_s]" << duration_cast<seconds>(p2 - p1).count()
		<< "[timeuse_milis]" << duration_cast<milliseconds>(p2 - p1).count()
		<< "[xxx]" << duration_cast<duration<int, std::ratio<1, 1000000>>>(p2 - p1).count() << endl;
	//	1  16612193642482445 time_t 1661219364
	//	3  523153593620700
	//	2  16612193664887254 time_t 1661219366
	//	4  523155835130400 used 2241509700
	//	[timeuse_defalut]22363088[timeuse_s]2[timeuse_milis]2236[timeuse_s]2[timeuse_milis]2236[xxx]2236308
}


void testtime5()
{
	// std::put_time()函数
	//此函数首先通过构造一个类型为basic_ostream::sentry的对象来访问输出序列。
	//然后（如果评估计算 sentry 对象为 true），它调用 time_put::put（使用流的选定区域设置）来执行格式化和插入操作，
	//相应地调整流的内部状态标志。 最后，它在返回之前销毁 sentry 对象。
	//它用于插入由tmb指向的时间和日期信息的表示，根据参数fmt指定来格式化。
	//声明
	//以下是 std::put_time 函数的声明。
	//template <class charT>
	///*unspecified*/ put_time(const struct tm* tmb, const charT * fmt);
	//参数
	//tmb − 指向类型struct tm的对象的指针，具有格式化的日期和时间信息。 struct tm是<ctime>头中定义的类。
	//fmt − time_put::put 使用C字符串作为格式字符串。它包含常规字符和特殊格式说明符的任意组合。这些格式说明符被函数替换为相应的值，以表示在tmb中指定的时间。
	//
	//格式都以百分比（％）符号开头，如下所示 -

	//格式都以百分比（％）符号开头，如下所示
	//	说明符   替换                                          示例
	//	% a       工作日名称的缩写* Thu
	//	% A       完整工作日名称* Thursday
	//	% b       月份名称缩写* Aug
	//	% B       完整月份名称* August
	//	% c       日期和时间表示                                Thu Aug 23 14:55 : 02 2019
	//	% C       年份除以100，并截断为整数（00 - 99）            20
	//	% d       月份中的某一天，用零填充（01 - 31）             23
	//	% D       MM / DD / YY日期的简写，相当于％m / ％d / ％y         08 / 23 / 19
	//	% e       月份中的某日，空格填充（1 - 31）                23
	//	% F       YYYY - MM - DD日期的简写，相当于％Y - ％m - ％d
	//	% g       基于周的年份，后两位数字（00 - 99）             01
	//	% G       一年中周                                      2001
	//	% h       月份名称的缩写（与％b相同）                   Aug
	//	% H       24小时格式（00 - 23）                           14
	//	% I       12小时格式（01 - 12）                           02
	//	% j       一年中的某日（001 - 366）                       235
	//	% m       月份的十进制数（01 - 12）                       08
	//	% M       分钟（00 - 59）                                 56
	//	% n       新行字符（'/n'）
	//	% p       指定AM或PM                                    PM
	//	% r       12小时时钟时间                                02:55 : 02 pm
	//	% R       24小时HH : MM时间，相当于％H : ％M                14 : 51
	//	% S       秒（00 - 61）                                   02
	//	% t       水平制表符（’ / t’）
	//	% T       ISO 8601时间格式(HH : MM : SS)，相当于 % H : % M : % S
	//	% u       ISO 8601工作日，星期一的数字为1（1 - 7）        4
	//	% U       周数，以第一个星期日为第一周的第一天（00 - 53） 33
	//	% V       ISO 8601周编号（00 - 53）                       34
	//	% w       工作日，使用十进制数，星期日为0（0 - 6）        4
	//	% W       周数，第一个星期一作为第一周的第一天（00 - 53）
	//	% x       日期的表示                                    08 / 23 / 01
	//	% X       时间的表示                                    14:55 : 02
	//	% y       年份，最后两位数字（00 - 99）                   01
	//	% Y       年份，四位数字                                2001
	//	% z       ISO 8601偏离UTC在时区（1分钟 = 1，1小时 = 100） + 100
	//	% Z       时区名称或缩写                                CDT
	//	% %％符号%


//#include <iostream>
//#include <iomanip>
//#include <ctime>
//#include <chrono>
	using std::chrono::system_clock;
	std::time_t tt = system_clock::to_time_t(system_clock::now());
	struct std::tm* ptm = std::localtime(&tt);
	std::cout << "Now (local time): " << std::put_time(ptm, "%c") << '/n';

}




void thread_foo()
{
	this_thread::sleep_for(std::chrono::seconds(1));
}
void thread_foo2()
{
	this_thread::sleep_for(std::chrono::seconds(1));
	cout << "[tid]" << this_thread::get_id() << endl;
}
void thread_foo3(thread *t)
{
	this_thread::sleep_for(std::chrono::seconds(1));
	cout << "[tid]" << t->get_id() << endl;
}
void testthread1()
{
	//重要的特性就是对线程进行支持了，使得C++在并行编程时不需要依赖第三方库，而且在原子操作中还引入了原子类的概念。
	//要使用标准库中的线程，必须包含< thread >头文件，该头文件声明了std::thread 线程类。
	//
	//线程的启动
	//C++线程库通过构造一个线程对象来启动一个线程，该线程对象中就包含了线程
	//运行时的上下文环境，比如：线程函数、线程栈、线程起始状态等以及线程ID
	//等，所有操作全部封装在一起，最后在底层统一传递给_beginthreadex()
	//创建线程函数来实现(注意：_beginthreadex是windows中创建线程的底层
	//	c函数)。
	//std::thread()创建一个新的线程可以接受任意的可调用对象类型（带参数或
	//者不带参数），包括lambda表达式（带变量捕获或者不带），函数，函数对象，
	//以及函数指针。	

	// 使用lambda表达式作为线程函数创建线程
	cout << "-------------------------------0" << std::endl;
	int n1 = 500;
	int n2 = 600;
	thread t([&](int addNum) {
		n1 += addNum;
		n2 += addNum;
		}, 500);

	t.join();
	std::cout << n1 << ' ' << n2 << std::endl;

	//线程的结束
	//启动了一个线程后，当这个线程结束的时候，如何去回收线程所使用的资源呢？thread库给我们两种选择：
	//加入式：join()
	//join()：会主动地等待线程的终止。在调用进程中join()，当新的线程终止时，join()会清理相关的资源，然后返回，调用线程再继续向下执行。
	//由于join()清理了线程的相关资源，thread对象与已销毁的线程就没有关系了，因此一个线程的对象每次你只能使用一次join()，当你调用的join()之后joinable()就将返回false了。

	cout << "-------------------------------1" << std::endl;
	thread t1(thread_foo);
	cout << "before join, joinable=" << t1.joinable() << std::endl;
	t1.join();
	cout << "after join, joinable=" << t1.joinable() << endl;
	cout << "-------------------------------1__" << std::endl;

	cout << "-------------------------------2" << std::endl;
	thread t2(thread_foo2);
	cout << "get tid" << std::endl;
	t2.join();
	cout << "-------------------------------2__" << std::endl;

	cout << "-------------------------------3" << std::endl;
	thread *t3;
	t3 = new thread(thread_foo3, t3);	
	t3->join();
	cout << "-------------------------------3__" << std::endl;

	//分离式：deatch（）
	//detach：会从调用线程中分理出新的线程，之后不能再与新线程交互。
	//分离的线程会在后台运行，其所有权和控制权将会交给c++运行库。同时，C++运行库保证，当线程退出时，其相关资源的能够正确的回收。
	//注意：必须在thread对象销毁之前做出选择，这是因为线程可能在你加入或分离线程之前，就已经结束了，之后如果再去分离它，线程可能会在thread对象销毁之后继续运行下去。一般分离式在线程入口函数处最开始定义。
	//原子性操作库(atomic)
	//为线程安全问题而生，也可以加锁解决。
	//原子变量库：#include
	//atomic_int: 即为int类的原子变量
	//atomic_char, atomic_short
	//总之只需要在内置类型前加上atomic_ 即可
	//原子变量多线程安全无需加锁
}

void ThreadFunc(int a)
{
	cout << "Thread1" << a << endl;
}
void ThreadFunc1(int& x)
{
	x += 10;
}
void ThreadFunc2(int* x)
{
	*x += 10;
}
void ThreadFunc3() { cout << "ThreadFunc()" << endl; }
bool DoSomething3() { return false; }
void ThreadFunc32() { cout << "ThreadFunc()" << endl; }
void Test32() { throw 1; }
void testthread2()
{

	//1 thread类的简单介绍
	// 函数名                      功能
	// thread()                    构造一个线程对象，没有关联任何线程函数，即没有启动任何线程
	// thread(fn, args1, args2, …) 构造一个线程对象，并关联线程函数fn，args1，args2，…为线程函数的参数
	// get_id()                    获取线程id
	// jionable()                  线程是否还在执行，joinable代表的是一个正在执行中的线程。
	// jion()                      该函数调用后会阻塞住线程，当该线程结束后，主线程继续执行
	// detach()                    在创建线程对象后马上调用，用于把被创建线程与线程对象分离开，分离的线程变为后台线程，创建的线程的"死活"就与主线程无关
	//
	//线程是操作系统中的一个概念，线程对象可以关联一个线程，用来控制线程以及获取线程的状态。
	//当创建一个线程对象后，没有提供线程函数，该对象实际没有对应任何线程。
	// 
	//get_id()的返回值类型为thread::id类型，id类型实际为std::thread命名空间下封装的一个类，该类中包含了一个结构体：
	//// vs下查看
	//typedef struct
	//{   /* thread identifier for Win32 */
	//	void* _Hnd; /* Win32 HANDLE */
	//	unsigned int _Id;
	//} _Thrd_imp_t;
	//
	//当创建一个线程对象后，并且给线程关联线程函数，该线程就被启动，与主线程一起运行。线程函数一般情况下可按照以下三种方式提供：
	//	函数指针
	//	lambda表达式
	//	函数对象

	{
		cout << "1 thread类的简单介绍" << endl;
		class TF
		{
		public:
			void operator()()
			{
				cout << "Thread3" << endl;
			}
		};
		// 线程函数为函数指针
		thread t1(ThreadFunc, 10);

		// 线程函数为lambda表达式
		thread t2([] {cout << "Thread2" << endl; });

		// 线程函数为函数对象
		TF tf;
		thread t3(tf);

		t1.join();
		t2.join();
		t3.join();
		cout << "Main thread!" << endl;
	}
	//thread类是防拷贝的，不允许拷贝构造以及赋值，但是可以移动构造和移动赋值，即将一个线程对象关联线程的状态转移给其他线程对象，转移期间不影响线程的执行。
	//可以通过jionable()函数判断线程是否是有效的，如果是以下任意情况，则线程无效
	//采用无参构造函数构造的线程对象
	//线程对象的状态已经转移给其他线程对象
	//线程已经调用jion或者detach结束
	//并发与并行的区别？
	//（1）并行是指两个或者多个事件在同一时刻发生；而并发是指两个或多个事件在同一时间间隔发生。
	//（2）并行是在不同实体上的多个事件，并发是在同一实体上的多个事件。
	//（3）在一台处理器上“同时”（这个同时实际上市交替“”）处理多个任务，在多台处理器上同时处理多个任务


	//2 线程函数参数
	//线程函数的参数是以值拷贝的方式拷贝到线程栈空间中的，
	//因此：即使线程参数为引用类型，在线程中修改后也不能修改外部实参，因为其实际引用的是线程栈中的拷贝，而不是外部实参。		

	{
		cout << "2 线程函数参数" << endl;
		int a = 10;

		// 在线程函数中对a修改，不会影响外部实参，因为：线程函数参数虽然是引用方式，但其实际引用的是线程栈中的拷贝
		//thread t1(ThreadFunc1, a);
		//t1.join();
		//cout << a << endl;

		// 如果想要通过形参改变外部实参时，必须借助std::ref()函数
		thread t2(ThreadFunc1, std::ref(a));
		t2.join();
		cout << a << endl;

		// 地址的拷贝
		thread t3(ThreadFunc2, &a);
		t3.join();
		cout << a << endl;
	}
	//注意：如果是类成员函数作为线程参数时，必须将this作为线程函数参数。


	//3 join与detach
	//启动了一个线程后，当这个线程结束的时候，如何去回收线程所使用的资源呢？thread库给我们两种选择：

	//join()方式
	// join()：主线程被阻塞，当新线程终止时，join()会清理相关的线程资源，然后返回，主线程再继续向下执行，然后销毁线程对象。
	// 由于join()清理了线程的相关资源，thread对象与已销毁的线程就没有关系
	// 了，因此一个线程对象只能使用一次join()，否则程序会崩溃。
	// jion()的误用一	
	{
		std::thread t(ThreadFunc3);
		if (!DoSomething3())
			cout << "!DoSomething3" << endl;

		t.join();
		cout << "DoSomething3" << endl;
	}
	/*
	说明：如果DoSomething()函数返回false,主线程将会结束，jion()没有调用，线程资源没有回收，
	造成资源泄漏。
	*/

	// jion()的误用二
	
	{
		int* p = new int[10];
		std::thread t(ThreadFunc32);
		try
		{
			Test32();
		}
		catch (...)
		{
			delete[] p;
			throw;
		}

		t.join();
	}

	//因此：采用jion()方式结束线程时，jion()的调用位置非常关键。为了避免该问题，可以采用RAII的方式对线程对象进行封装，比如

	//detach()方式
	//detach()：该函数被调用后，新线程与线程对象分离，不再被线程对象所表达，就不能通过线程对象控制线程了，
	// 新线程会在后台运行，其所有权和控制权将会交给c++运行库。同时，C++运行库保证，当线程退出时，其相关资源的能够正确的回收。
	//detach()函数一般在线程对象创建好之后就调用，因为如果不是jion()等待方式结束，那么线程对象可能会在新线程结束之前被销毁掉而导致程序崩溃。
	// 因为std::thread的析构函数中，如果线程的状态是jionable，std::terminate将会被调用，而terminate()函数直接会终止程序。
	//因此：线程对象销毁前，要么以jion()的方式等待线程结束，要么以detach()的方式将线程与线程对象分离。



	//4 原子性操作库(atomic)
	//多线程最主要的问题是共享数据带来的问题(即线程安全)。如果共享数据都是只读的，那么没问题，因为只读操作不会影响到数据，
	//更不会涉及对数据的修改，所以所有线程都会获得同样的数据。但是，当一个或多个线程要修改共享数据时，就会产生很多潜在的麻烦。比如
	
	//contained type	    atomic type	          description
	//bool                  atomic_bool
	//char                  atomic_char	          atomics for fundamental integral types.
	//signed char	        atomic_schar          These are either typedefs of the corresponding full specialization of the atomic class template or a base class of such specialization.
	//unsigned char	        atomic_uchar
	//short	                atomic_short
	//unsigned short	    atomic_ushort
	//int                   atomic_int
	//unsigned int          atomic_uint
	//long                  atomic_long
	//unsigned long         atomic_ulong
	//long long             atomic_llong
	//unsigned long long    atomic_ullong
	//wchar_t               atomic_wchar_t
	//char16_t              atomic_char16_t
	//char32_t              atomic_char32_t
	//intmax_t              atomic_intmax_t	      atomics for width - based integrals(those defined in <cinttypes>).
	//uintmax_t             atomic_uintmax_t      Each of these is either an alias of one of the above atomics for fundamental integral types or of a full specialization of the atomic class template with an extended integral type.
	//int_leastN_t          atomic_int_leastN_t   Where N is one in 8, 16, 32, 64, or any other type width supported by the library.
	//uint_leastN_t         atomic_uint_leastN_t
	//int_fastN_t           atomic_int_fastN_t
	//uint_fastN_t          atomic_uint_fastN_t
	//intptr_t              atomic_intptr_t
	//uintptr_t             atomic_uintptr_t
	//size_t                atomic_size_t
	//ptrdiff_t             atomic_ptrdiff_t

	{
		std::mutex m;
		unsigned long sum = 0L;

		auto func4 = [&](size_t num)
		{
			for (size_t i = 0; i < num; ++i)
			{
				m.lock();
				sum++;
				m.unlock();
			}
		};


		cout << "Before joining,sum = " << sum << std::endl;

		thread t1(func4, 10000000);
		thread t2(func4, 10000000);
		t1.join();
		t2.join();

		cout << "After joining,sum = " << sum << std::endl;
	}

	//虽然加锁可以解决，但是加锁有一个缺陷就是：只要一个线程在对sum++时，其他线程就会被阻塞，会影响程序运行的效率，而且锁如果控制不好，还容易造成死锁。
	//因此C++11中引入了原子操作。所谓原子操作：即不可被中断的一个或一系列操作，C++11引入的原子操作类型，使得线程间数据的同步变得非常高效。

	//注意：需要使用以上原子操作变量时，必须添加头文件
	//#include <atomic>

	
	{
		atomic_long sum{ 0 };

		auto func4 = [&](size_t num)
		{
			for (size_t i = 0; i < num; ++i)
				sum++;   // 原子操作
		};

		cout << "Before joining, sum = " << sum << std::endl;

		thread t1(func4, 1000000);
		thread t2(func4, 1000000);
		t1.join();
		t2.join();

		cout << "After joining, sum = " << sum << std::endl;
	}

	//在C++11中，程序员不需要对原子类型变量进行加锁解锁操作，线程能够对原子类型变量互斥的访问。
	//更为普遍的，程序员可以使用atomic类模板，定义出需要的任意原子类型

	//atmoic<T> t;    // 声明一个类型为T的原子类型变量t
	//注意：原子类型通常属于"资源型"数据，多个线程只能访问单个原子类型的拷贝，因此在C++11中，原子类型只能从其模板参数中进行构造，
	//不允许原子类型进行拷贝构造、移动构造以及operator = 等，为了防止意外，标准库已经将atmoic模板类中的拷贝构造、移动构造、赋值运算符重载默认删除掉了。

#include <atomic>
	{
		atomic<int> a1(0);
		//atomic<int> a2(a1);    // 编译失败
		atomic<int> a2(0);
		//a2 = a1;               // 编译失败
	}


	//5 lock_guard与unique_lock
	//在多线程环境下，如果想要保证某个变量的安全性，只要将其设置成对应的原子类型即可，即高效又不容易出现死锁问题。
	// 但是有些情况下，我们可能需要保证一段代码的安全性，那么就只能通过锁的方式来进行控制。
	//
	//5.1 Mutex的种类
	//在C++11中，Mutex总共包了四个互斥量的种类：
	//
	//1. std::mutex
	//C++11提供的最基本的互斥量，该类的对象之间不能拷贝，也不能进行移动。mutex最常用的三个函数：
	//
	//函数名	函数功能
	//lock()	上锁：锁住互斥量
	//unlock()	解锁：释放对互斥量的所有权
	//try_lock()	尝试锁住互斥量，如果互斥量被其他线程占有，则当前线程也不会被阻塞
	//注意，线程函数调用lock()时，可能会发生以下三种情况：
	//
	//如果该互斥量当前没有被锁住，则调用线程将该互斥量锁住，直到调用 unlock之前，该线程一直拥有该锁
	//如果当前互斥量被其他线程锁住，则当前的调用线程被阻塞住
	//如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)
	//线程函数调用try_lock()时，可能会发生以下三种情况：
	//
	//如果当前互斥量没有被其他线程占有，则该线程锁住互斥量，直到该线程调用 unlock 释放互斥量
	//如果当前互斥量被其他线程锁住，则当前调用线程返回 false，而并不会被阻塞掉
	//如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)
	//2. std::recursive_mutex
	//其允许同一个线程对互斥量多次上锁（即递归上锁），来获得对互斥量对象的多层所有权，
	// 释放互斥量时需要调用与该锁层次深度相同次数的 unlock()，
	// 除此之外，std::recursive_mutex 的特性和std::mutex 大致相同。
	//
	//3. std::timed_mutex
	//比 std::mutex 多了两个成员函数，try_lock_for()，try_lock_until() 。
	//
	//try_lock_for()
	//接受一个时间范围，表示在这一段时间范围之内线程如果没有获得锁则被阻塞住（与 std::mutex的 try_lock() 不同，
	// try_lock 如果被调用时没有获得锁则直接返回 false），如果在此期间其他线程释放了锁，
	// 则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 false。
	//try_lock_until()
	//接受一个时间点作为参数，在指定时间点未到来之前线程如果没有获得锁则被阻塞住，如果在此期间其他线程释放了锁，
	// 则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 false。
	//4. std::recursive_timed_mutex
	// 
	//5.2 lock_guard
	//std::lock_gurad 是 C++11 中定义的模板类。定义如下：
	//
	//template<class _Mutex>
	//class lock_guard
	//{
	//public:
	//	// 在构造lock_gard时，_Mtx还没有被上锁
	//	explicit lock_guard(_Mutex& _Mtx)
	//		: _MyMutex(_Mtx)
	//	{
	//		_MyMutex.lock();
	//	}

	//	// 在构造lock_gard时，_Mtx已经被上锁，此处不需要再上锁
	//	lock_guard(_Mutex& _Mtx, adopt_lock_t tag)
	//		: _MyMutex(_Mtx)
	//	{}

	//	~lock_guard() _NOEXCEPT
	//	{
	//		_MyMutex.unlock();
	//	}

	//	lock_guard(const lock_guard&) = delete;
	//	lock_guard& operator=(const lock_guard&) = delete;

	//private:
	//	_Mutex& _MyMutex;
	//};

	//lock_guard类模板主要是通过RAII的方式，对其管理的互斥量进行了封装，在需要加锁的地方，
	//只需要用上述介绍的任意互斥体实例化一个lock_guard，调用构造函数成功上锁，出作用域前，
	//lock_guard对象要被销毁，调用析构函数自动解锁，可以有效避免死锁问题。
	//lock_guard的缺陷：太单一，用户没有办法对该锁进行控制，因此C++11又提供了unique_lock。

	{
		mutex mu;
		lock_guard<mutex> lock(mu);
	}

	//5.3 unique_lock
	//与lock_gard类似，unique_lock类模板也是采用RAII的方式对锁进行了封装，
	//并且也是以独占所有权的方式管理mutex对象的上锁和解锁操作，即其对象之间不能发生拷贝。
	//在构造(或移动(move)赋值)时，unique_lock 对象需要传递一个 Mutex 对象作为它的参数，
	//新创建的 unique_lock 对象负责传入的 Mutex对象的上锁和解锁操作。
	//使用以上类型互斥量实例化unique_lock的对象时，自动调用构造函数上锁，
	// unique_lock对象销毁时自动调用析构函数解锁，可以很方便的防止死锁问题。
	//与lock_guard不同的是，unique_lock更加的灵活，提供了更多的成员函数：
	//上锁 / 解锁操作：lock、try_lock、try_lock_for、try_lock_until和unlock
	//修改操作：移动赋值、交换(swap：与另一个unique_lock对象互换所管理的互斥量所有权)、释放(release：返回它所管理的互斥量对象的指针，并释放所有权)
	//获取属性：owns_lock(返回当前对象是否上了锁)、operator bool()(与owns_lock()的功能相同)、mutex(返回当前unique_lock所管理的互斥量的指针)。
		
}


void testthread3()
{

}


void testthread4()
{

}



//regex_match
void testregex1()
{
	//regex 库中涉及到的主要类型有：
	//以std::string为代表的处理字符串的类型（我们知道还有存储wchar_t的wstring类、原生c式字符串const char* 等等，
	//  为了简化处理仅介绍std::string类型相关的操作，当你把握住了regex的主脉络之后，想使用其他的版本只要类比就可以）
	//std::regex类，该类型需要一个代表正则表达式的字符串和一个文法选项作为输入，当文法选项不提供时默认为ECMAScript。
	//std::match_results类，该类用来记录匹配的结果，这是一个模板类，该类的模板参数是一个迭代器类型，
	//  对于std::string来说我们定义了smatch作为match_results<string::const_iterator>作为别名。
	//std::sub_match类，该类其实封装了两个迭代器，第一个代表开始部分，第二个代表结束部分，就像你用两个下表索引去表达一个字符串的某一个子串一样。
	//  这个类就是通过这样的方式提供原字符串的某一个子串作为结果。实际上match_results中就封装了一些std::sub_match类型的对象。
	//  （为什么是一些而不是一个，因为一次匹配可能会产生多个结果返回，regex认为每个括号对构成一个子匹配项，regex匹配的结果可以显式每个子匹配项匹配到的内容。）
	//现在我们有了表达字符串的类，表达正则匹配的类，表达匹配结果的类，接下来regex提供三个匹配函数：
	//  bool std::regex_match(...)
	//  bool std::regex_search(...)
	//  string std::regex_replace(...)//实际上返回类型是根据你输入的数据类型对应的basic_string类。
	//首先说明三个函数功能上的不同，std::regex_match是全文匹配，即它希望你输入的字符串要和正则表达式全部匹配，才认为匹配成功，否则匹配失败，
	//  而std::regex_search是在你输入的字符串中不断搜索符合正则表达式描述的子字符串，然后将第一个匹配到的子字符串返回。
	//  std::regex_replace是在std::regex_search的基础上更进一步，可以将匹配的子字符串替换为你提供的字符串。


	//使用正则表达式，你就必须包含所需的头文件regex, 里面包含了所需的函数，一般的第一步需要确定要匹配的模式pattern, 
	//使用regex类型进行定义regex pattern("要匹配的正则表达式模式")，
	//其次一般的常用操作就是灵活的运用regex_match, regex_search, regex_replace这三个函数，
	//后面还有几个用的不太多的函数regex_iterator后续会介绍：

	//regex_match的相关及举例
	//原型大致为：
	//bool regex_match(const basic_string<charT, ST, SA>&s,
	//	const basic_regex<charT, traits>&rgx,
	//	regex_constants::match_flag_type flags = regex_constants::match_default);
	// 
	//  第一个参数s为：需要用正则表达式去匹配的字符串，简言之就是要处理的字符串。
	//  第二个参数rgx为：为一个basic_regex的一个对象，也就是你要进行匹配的模式，用正则字符串表示，其声明为:
	//    (1)typedef basic_regex<char>    regex;//正常字符处理（常用）
	//    (2)typedef basic_regex<wchar_t> wregex;//宽字符处理
	//  第三个参数flags是控制第二个参数如何去匹配，第三个参数处可以设置一个或多个常量去控制，一般设置有默认值
	//  返回值为：如果匹配成功，返回True,否则返回False
	//  
	

	cout << "testregex1------------------" << endl;
	//此为匹配字符串"wdw9078798asadada"，是否满足匹配正则表达式所要求的条件，
	//regex{ "[A-Z]{1,3}.*"}:目的是匹配由1个到三个字母开头的字符串，匹配成功时返回true,否则返回false
	bool status = false;
	string str1 = "wdw9078798asadada";
	status = regex_match(str1, regex{ "[a-z]{1,3}.*" }); //第三个参数为忽略大小写
	if (status == true) {
		printf("匹配成功！\n");
	}
	else {
		printf("匹配失败！\n");
	}
	//结果为匹配成功！

	//当然在regex定义时，可以指定第二个参数类型flag_type为控制regex的属性，构造函数声明如下：
	//explicit basic_regex(
	//	const basic_string<_Elem, _STtraits, _STalloc>&_Str,
	//	flag_type _Flags = regex_constants::ECMAScript)
	//
	//第一个参数不用说，就是指定一个字符串，为要匹配的正则式，
	//第二个参数为指定属性，之前已经用到的一个为regex_constants::icase, 表示忽略大小写进行匹配，也可以写成regex::icase, 
	//但源码中为regex_constants::？这种形式，所以采用这种写法，其中的声明还有：

	//来自regex中的声明
	//static constexpr flag_type icase = regex_constants::icase;//忽略大小写
	//static constexpr flag_type nosubs = regex_constants::nosubs;//子无表达式，
	//static constexpr flag_type optimize = regex_constants::optimize;//优化匹配，匹配效率优于构造regex对象的效率。
	//static constexpr flag_type collate = regex_constants::collate;//区域敏感性
	//static constexpr flag_type ECMAScript = regex_constants::ECMAScript;//默认的语法
	//static constexpr flag_type basic = regex_constants::basic;//基础的posix语法
	//static constexpr flag_type extended = regex_constants::extended;//扩展posix语法
	//static constexpr flag_type awk = regex_constants::awk;
	//static constexpr flag_type grep = regex_constants::grep;
	//static constexpr flag_type egrep = regex_constants::egrep;

	status = regex_match(str1, regex{ "[A-Z]{1,3}.*"}); // 默认不忽略大小写
	if (status == true) {
		printf("匹配成功！\n");
	}
	else {
		printf("匹配失败！\n");
	}

	status = regex_match(str1, regex("[A-Z]{1,3}.*")); // 注意 { （ 效果一样
	if (status == true) {
		printf("匹配成功！\n");
	}
	else {
		printf("匹配失败！\n");
	}

	status = regex_match(str1, regex{ "[A-Z]{1,3}.*",regex_constants::icase }); //第三个参数为忽略大小写
	if (status == true) {
		printf("匹配成功！\n");
	}
	else {
		printf("匹配失败！\n");
	}
}


// regex_search
void testregex2()
{
	//bool regex_search(const basic_string<charT, ST, SA>&s,
	//	const basic_regex<charT, traits>&rgx,
	//	regex_constants::match_flag_type flags = regex_constants::match_default);
	//  参数含义与regex_match一致，此方法不返回匹配成功的字符串，只是确定里面是否有满足正则式的字句
	// 
	//bool regex_search(const basic_string<charT, ST, SA>&s,
	//	match_results<typename basic_string<charT, ST, SA>::const_iterator, Alloc>&m,
	//	const basic_regex<charT, traits>&rgx,
	//	regex_constants::match_flag_type flags = regex_constants::match_default);
	// 其他参数含义一样，多了一个m参数，其含义为此处为一个match_results的类型，其作用是存储匹配的结果或者满足子表达式匹配的结果，返回结果为一个迭代器

	cout << "testregex2------------------" << endl;
	{
		/*此程序的regex为regex("[0-9]{2}[a-z]{1,4}[0-9]{2}")
		*/
		smatch result;
		string str1("i89love78you,mrsLu");
		bool sta = regex_search(str1, result, regex("[0-9]{2}[a-z]{1,4}[0-9]{2}"));
		for (const auto &it : result)
		{
			cout << it.str() << endl;
		}
		/*结果：
			89love78
		*/
	}
	
	{
		//此程程序中的regex为regex("([0-9]{2})([a-z]{1,4})([0-9]{2})")注意中间有括号和没有括号的区别
		smatch result;
		string str1("i89love78you,mrsLu");
		bool sta = regex_search(str1, result, regex("([0-9]{2})([a-z]{1,4})([0-9]{2})"));
		for (const auto& it : result) {
			cout << it.str() << endl;
		}
		/*当有子表达式匹配时，访问匹配结果中的存储为：
		第一个存储的结果为满足整个正则匹配式的字符串，从第二个开始，依次存储从左向右的每个圆括号中的匹配式的结果，所以可以进行以下访问：
		cout << result[0] << endl; //输出89love78
		cout << result.str(0) << endl; //输出89love78
		二者等效，
		cout << result.str(1) << endl; //输出89
		cout << result.str(2) << endl; //输出love
		cout << result.str(3) << endl; //输出78
		*/
		/*结果：
			89love78
			89
			love
			78
		*/
	}

	{
		//从以上两个程序结果可以看出，smatch存储的结果为以()为子匹配式进行匹配，在某些时候这种方式可以起到非常大的作用。
		//当然regex_results对象有两个方法suffix()和prefix()分别显示的为匹配结果的后缀和前缀，上述的匹配结果进行调用有如下信息：

		smatch result;
		string str1("i89love78you,mrsLu");
		bool sta = regex_search(str1, result, regex("[0-9]{2}[a-z]{1,4}[0-9]{2}"));
		cout << "后缀为：" << result.suffix().str() << endl << "前缀为：" << result.prefix().str() << endl;
		/*结果：
			后缀为：you,mrsLu
			前缀为：i
		*/
	}
}


//regex_replace
void testregex3()
{
	//regex_replace可以查找匹配正则表达式的字符串并使用其它格式来替换，可以是自己想要替换的普通字符串，也可以是$指定
	//原型声明：
	//template <class traits, class charT, class ST, class SA>
	//	basic_string<charT, ST, SA> regex_replace(const basic_string<charT, ST, SA>&s,
	//	const basic_regex<charT, traits>&rgx,
	//	const charT * fmt,
	//	regex_constants::match_flag_type flags = regex_constants::match_default);
	//第一个参数s表示要被操作的字符串对象
	//第二个参数rgx为匹配正则表达式
	//第三个参数fmt为以何种方式进行替换
	//第四个参数flags为一种方式，代表怎样去替换
	//返回值为：如果匹配成功返回已经替换成功的字符串，否则匹配失败，返回原字符串

	//第三个参数的设置如下表（来自c++ reference）其中（第三个为$`,第四个为$’）：
	//characters	replacement
	//	$n	n - th backreference(i.e., a copy of the n - th matched group specified with parentheses in the regex pattern).
	//	n must be an integer value designating a valid backreference, greater than 0, and of two digits at most.
	//	$& A copy of the entire match
	//	$`	The prefix(i.e., the part of the target sequence that precedes the match).
	//	$´	The suffix(i.e., the part of the target sequence that follows the match).
	//	$$	A single $ character.

	//第四个参数的设置常量如下表（来自c++ reference）这些常量全都在regex_contants命名空间中有声明:
	//flag* effects	notes
	//	match_default	Default	Default matching behavior.
	//	This constant has a value of zero** .
	//	match_not_bol	Not Beginning - Of - Line	The first character is not considered a beginning of line("^" does not match).
	//	match_not_eol	Not End - Of - Line	The last character is not considered an end of line("$" does not match).
	//	match_not_bow	Not Beginning - Of - Word	The escape sequence "\b" does not match as a beginning - of - word.
	//	match_not_eow	Not End - Of - Word	The escape sequence "\b" does not match as an end - of - word.
	//	match_any	Any match	Any match is acceptable if more than one match is possible.
	//	match_not_null	Not null	Empty sequences do not match.
	//	match_continuous	Continuous	The expression must match a sub - sequence that begins at the first character.
	//	Sub - sequences must begin at the first character to match.
	//	match_prev_avail	Previous Available	One or more characters exist before the first one. (match_not_bol and match_not_bow are ignored)
	//	format_default	Default formatting	Uses the standard formatting rules to replace matches(those used by ECMAScript's replace method).
	//		This constant has a value of zero * *.
	//		format_sed	sed formatting	Uses the same rules as the sed utility in POSIX to replace matches.
	//		format_no_copy	No copy	The sections in the target sequence that do not match the regular expression are not copied when replacing matches.
	//		format_first_only	First only	Only the first occurrence of a regular expression is replaced.

	regex pattern("([0-9]{4})-([0-9]{2})-([0-9]{2})");
	regex r(pattern);
	string date = "日期为：2020-08-04 2020-05-30";
	cout << regex_replace(date, r, "$1.$2.$3") << endl;
	/*结果：
		日期为:2020.08.04 2020.05.30
	*/

	//当然，也可以设置regex_replace第四那个参数，设置将字符串中没有被匹配的部分不输出
	cout << regex_replace(date, r, "$1.$2.$3", regex_constants::format_no_copy) << endl;
	//输出为2020.08.042020.05.30
	
	//最常使用的为进行普通字符串的替代
	//将字符串中的大写字母换为_
	regex patt("[A-Z]");
	string s = "www.asxWscnsj.com";
	cout << regex_replace(s, patt, "_") << endl;
	//执行结果www.asx_scnsj.com	
}


//match_results
//regex_error
//regex_iterator
void testregex4()
{
	//match_results
		//typedef match_results<const char*> cmatch;
		//typedef match_results<const wchar_t*> wcmatch;
		//typedef match_results<string::const_iterator> smatch;  //(常用)
		//typedef match_results<wstring::const_iterator> wsmatch;
		//上面为regex头文件中的宏声明，常用的为smatch，例子见regex_search栏

	//regex_error
		//class regex_error : public runtime_error { /* ... */ };
		//由此可见，该异常类继承自runtime_error类。
		//异常描述：
		//此异常类型的对象由正则表达式库的元素引发。
		//它继承了标准异常runtime_error，并有一个特殊的公共成员函数, 它根据引发它的错误的类型返回regex_constants:：error_type的特定代码：
	//flag	error
	//	error_collate	The expression contained an invalid collating element name.
	//	error_ctype	The expression contained an invalid character class name.
	//	error_escape	The expression contained an invalid escaped character, or a trailing escape.
	//	error_backref	The expression contained an invalid back reference.
	//	error_brack	The expression contained mismatched brackets([and]).
	//	error_paren	The expression contained mismatched parentheses((and)).
	//	error_brace	The expression contained mismatched braces({ and }).
	//	error_badbrace	The expression contained an invalid range between braces({ and }).
	//	error_range	The expression contained an invalid character range.
	//	error_space	There was insufficient memory to convert the expression into a finite state machine.
	//	error_badrepeat	The expression contained a repeat specifier(one of * ? +{) that was not preceded by a valid regular expression.
	//	error_complexity	The complexity of an attempted match against a regular expression exceeded a pre - set level.
	//	error_stack	There was insufficient memory to determine whether the regular expression could match the specified character sequence.


	try
	{
		std::regex myregex("*");
	}
	catch (std::regex_error& e)
	{
		std::cerr << "error code:" << e.code() << ":" << e.what() << std::endl;
	}
	/*
		error code:10:regex_error(error_badrepeat): One of *?+{ was not preceded by a valid regular expression.
	*/

	//regex_iterator
	//构造方法：
	//无参构造函数：regex_iterator();
	//拷贝构造函数：regex_iterator(const regex_iterator & rit)
	//初始化构造函数：regex_iterator(BidirectionalIterator first,
	//		BidirectionalIterator last,
	//		const regex_type & rgx,
	//		regex_constants::match_flag_type flags = regex_constants::match_default);
	//初始化构造函数的第四个参数与regex_replace的第四个参数的含义一样，复制选项也一样，可参考上述文章

	//                    tab
	std::string s("this sub	123 subject has a submarine as a subsequence");
	std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"，后跟非空白字符，遇到空格会终止

	std::regex_iterator<std::string::iterator> rit(s.begin(), s.end(), e);
	std::regex_iterator<std::string::iterator> rend;

	while (rit != rend)
	{
		std::cout << rit->str();
		std::cout << std::endl;
		++rit;
	}
	/*
	  输出为：
	  sub	123
	  subject
	  submarine
	  subsequence
  */

}


void testhashmap()
{
	//hash_map和unordered_map的区别：
	//这里为什么将二者一起说呢？因为hash_map和unordered_map都是用哈希表实现的，它们有什么区别吗？
	//其实区别不大，但是推荐使用unordered_map，因为unordered_map在C++11就被录入标准库了，而hash并没有进入标准库。

	//错误	C1189	#error:  <hash_map> is deprecated and will be REMOVED. Please use <unordered_map>. You can define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS to acknowledge that you have received this warning.	stlTest	C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Tools\MSVC\14.29.30133\include\hash_map	22	
	//解决方法：
	//1)使用unordered_map代替hash_map(推荐)
	//2)在项目属性->c / c++->预编译器，增加   _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 定义
	//3)在使用include之前，加上      #define 	_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 定义


	stdext::hash_map<string, string> hmss;
	hmss["1"] = "111";
	hmss["2"] = "222";
	hmss["3"] = "333";

	for (auto it : hmss)
	{
		printf("%s : %s\n", it.first.c_str(), it.second.c_str());
	}

	std::unordered_map<string, string> umss;
	umss["11"] = "111";
	umss["12"] = "222";
	umss["13"] = "333";

	for (auto it : umss)
	{
		printf("%s : %s\n", it.first.c_str(), it.second.c_str());
	}

}

void testfloat1()
{
	double d1 = 1.1;
	double d2 = -1.1;
	double d3 = DBL_MAX;
	double d4 = DBL_MAX + DBL_MAX + +DBL_MAX;

	int i1 = _finite(d1);
	int i2 = _finite(d2);
	int i3 = _finite(d3);
	int i4 = _finite(d4);

	printf("i1 %d d1 = %f\n", i1, d1);
	printf("i2 %d d2 = %f\n", i2, d2);
	printf("i3 %d d3 = %f\n", i3, d3);
	printf("i4 %d d4 = %f\n", i4, d4);
	printf("i4 %d d4 = %s\n", i4, &d4);
}

