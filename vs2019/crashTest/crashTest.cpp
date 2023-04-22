// crashTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>

using namespace std;

void mapDel2Times();



int main()
{
    mapDel2Times();

    std::cout << "Hello World!\n";
}




void mapDel2Times()
{
    map<string, int*> map1;

    map1["1"] = new int(1);
    map1["2"] = new int(2);
    map1["3"] = new int(3);
    map1["4"] = new int(4);
    map1["5"] = new int(5);



    map<string, int*>::iterator it;


    for (it = map1.begin(); it != map1.end(); it++)
    {
        delete it->second;
        it->second = NULL;
    }



	for (it = map1.begin(); it != map1.end(); it++)
	{
		delete it->second;
	}






}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
