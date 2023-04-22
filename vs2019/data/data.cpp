// data.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdlib.h>

#include <iostream>


#include "array.h"
#include "array.cpp"

void testarray();
void testarray2();
void testarray3();
void testarray4();

#include "tree.h"
void testtree();
void testtree2();
void testtree3();
void testtree4();
void testtree5();

void testCurse();   //gotoxy
void testCurse2();   //\033
void testCurse3();   //\033

int main()
{
	//testarray3();
	//testtree();
	//testtree2();
	//testtree3();
	//testtree4();
	//testtree5();


	//testCurse();
	//testCurse2();
	testCurse3();

	//system("pause");
}

void testarray()
{
	wjg::array<int> ai;
	srand(time(0));
	for (int i = 0; i < 12; ++i)
	{
		ai.pushback(rand() % 32);
	}
	ai.print(8);
	ai.sortinsert();
	ai.print(8);
}

void testarray2()
{
	wjg::array<float> ai;
	srand(time(0));
	for (int i = 0; i < 12; ++i)
	{
		ai.pushback(0.1 * (rand() % 10) + (rand() % 32));
	}
	ai.print(8);
	ai.sortinsert();
	ai.print(8);
}


void testarray3()
{
	wjg::array<int> ai;
	srand(time(0));
	for (int i = 0; i < 12; ++i)
	{
		ai.pushback(rand() % 32);
	}
	ai.print(8);
	ai.sortbubble();
	ai.print(8);
}


void testarray4()
{
	wjg::array<int> ai;
	srand(time(0));
	for (int i = 0; i < 12; ++i)
	{
		ai.pushback(rand() % 32);
	}
	ai.print(8);
	ai.sortquick();
	ai.print(8);
}


void testtree()
{
	wjg::tree_simple_avl2 tree2;

	tree2.insert(1);
	tree2.insert(2);
	tree2.insert(3);
	tree2.insert(4);
	tree2.insert(5);

	tree2.print();
}

void testtree2()
{
	wjg::tree_simple_avl2 tree2;

	tree2.insert(13);
	tree2.insert(6);
	tree2.insert(1);
	tree2.insert(8);
	tree2.insert(5);

	tree2.insert(23);
	tree2.insert(15);
	tree2.insert(26);
	tree2.insert(17);
	tree2.insert(22);
	tree2.insert(21);

	tree2.print();
}

void testtree3()
{
	wjg::tree_simple_avl tree2;
	int y = 0;
	//printf("123321\n");
	tree2.insert(13);
	tree2.insert(6);
	tree2.insert(16);
	tree2.insert(1);
	tree2.insert(8);
	tree2.insert(5);

	tree2.insert(23);
	tree2.insert(15);
	tree2.insert(26);
	tree2.insert(17);
	tree2.insert(22);
	tree2.insert(21);


	tree2.insert(31);
	tree2.insert(32);
	tree2.insert(33);
	tree2.insert(34);
	tree2.insert(35);
	tree2.insert(36);

	tree2.insert(41);
	tree2.insert(42);
	tree2.insert(43);
	tree2.insert(44);
	tree2.insert(45);
	tree2.insert(46);

	tree2.insert(51);
	tree2.insert(52);
	tree2.insert(53);
	tree2.insert(54);
	tree2.insert(55);
	tree2.insert(56);

	y = tree2.print();

	
	tree2.erase(41);

	y += tree2.print(y);

	tree2.erase(42);

	y += tree2.print(y);


	tree2.erase(43);
	tree2.erase(44);
	tree2.erase(45);
	tree2.erase(46);
		  
	tree2.erase(51);
	tree2.erase(52);
	tree2.erase(53);
	tree2.erase(54);
	tree2.erase(55);
	tree2.erase(56);
	//printf("\033[2J");  // 清屏
	y += tree2.print(y);

	//gotoxy(0, 0); printf("    a\n");
	//gotoxy(0, 1); printf("  b\n");
	//gotoxy(0, 2); printf("c\n");	
	//gotoxy(5, 1); printf("h\n");      ⬎⬏⬐⬑↵↓↔←→↑
	//gotoxy(6, 1); printf("  d\n");	---⬎⬏⬐⬑↵↓↔←→↑

	//gotoxy(5, 2); printf("    e\n");

	//gotoxy(0, y);
	printf("\n");
}


void testtree4()
{
	wjg::tree_simple_avl tree2;
	int y = 0;

	for (int i = 0; i < 127; i++)
	{
		tree2.insert(i);
	}

	y = tree2.print();

	for (int i = 0; i < 90; i++)
	{
		tree2.erase(i);
	}

	y += tree2.print(y);

	printf("\n");
}

void testtree5()
{
	wjg::tree_simple_avl tree2;
	int y = 0;

	for (int i = 0; i < 31; i++)
	{
		tree2.insert(i);
	}

	y = tree2.print();

	tree2.preoder();
	tree2.midoder();
	tree2.postoder();
	y += 3 * 3;

	for (int i = 5; i < 111; i++)
	{
		tree2.erase(i);
	}

	y += tree2.print(y);

	tree2.preoder();
	tree2.midoder();
	tree2.postoder();
	y += 3 * 3;

	printf("\n");
}

void testCurse()
{
	//gotoxy(int x, int y)是 Borland C 扩充函数库 conio.h 中声明的一个函数，功能是将光标移动到指定位置。在当代的 Visual C++ 或 GCC 中可以自定义这个函数。
	//gotoxy(int x, int y) 左上角坐标为 0 0
	gotoxy(0, 0);
	printf("a");

	gotoxy(1, 1);
	printf("b");

	gotoxy(2, 2);
	printf("c");

	gotoxy(3, 3);
	printf("d");
}

void testCurse2()
{
	//构建16257（及更高版本）的Windows 10控制台主机中已经支持ANSI颜色控制了，默认不开启，需要配置注册表如下值：
	//HKEY_CURRENT_USER\Console\VirtualTerminalLevel
	// 
	// 
	//在上文中用到在控制台输出不用的颜色在区别apache error log中不同严重等级的错误输出。ANSI Color的说明见下：
	//背景颜色范围:40----49
	//40 : 黑 41 : 深红 42 : 绿 43 : 黄色 44 : 蓝色 45 : 紫色 46 : 深绿 47 : 白色
	//字颜色 : 30---------- - 39
	//30 : 黑 31 : 红 32 : 绿 33 : 黄 34 : 蓝色 35 : 紫色 36 : 深绿 37 : 白色
	//== = ANSI控制码的说明 == =
	//\33[0m 关闭所有属性
	//\33[1m 设置高亮度
	//\33[4m 下划线
	//\33[5m 闪烁
	//\33[7m 反显
	//\33[8m 消隐
	//\33[30m-- \33[37m 设置前景色
	//\33[40m-- \33[47m 设置背景色
	//\33[nA 光标上移n行
	//\33[nB 光标下移n行
	//\33[nC 光标右移n行
	//\33[nD 光标左移n行
	//\33[x;yH设置光标位置                    左上角坐标为1 1
	//\33[2J 清屏
	//\33[K 清除从光标到行尾的内容
	//\33[s 保存光标位置
	//\33[u 恢复光标位置
	//\33[? 25l 隐藏光标
	//\33[? 25h 显示光标

	printf("\033[2J");  // 清屏
	printf("\033[1;1Habc");  // 坐标 1 1 打印 abc
	
	printf("\033[40m\033[43m");  // 背景色 43
	printf("\033[30m\033[35m");  // 前景色 35
	printf("123");             // 打印 123

	printf("\033[40m\033[42m");  // 背景色 43
	printf("\033[30m\033[33m");  // 前景色 35
	printf("456");             // 打印 123

	
	printf("\033[7m");             // 背景前景调换
	printf("789");             // 打印 123

	printf("\033[5m");             // 闪烁
	printf("123");             // 打印 123

	printf("\033[4m");             // 下划线
	printf("123");             // 打印 123

	printf("\033[8m");             // 消隐
	printf("123");             // 打印 123

	printf("\033[1m");             // 设置高亮度
	printf("123");             // 打印 123

	printf("\033[? 25l");          // 清除所有设置


	printf("\033[0m");          // 清除所有设置

	//printf("\033[3;3Habc");

}

void testCurse3()
{
	//简介
	//在此，不介绍Windows程序控制台中使用Windows.h库中的setconsoletextattribute函数，仅介绍\033控制字符(ESC)的方法。该方法可以直接适用于printf()函数中。
	//其中，\033(八进制)即ESC符号，Windows中为\027(十进制)，\x1b(十六进制)
	//
	//格式
	//开始格式：
	//\033[参数1; 参数2; 参数3 m  //以字母m结尾
	//
	//内容格式：
	//正常的printf中的参数及内容
	//
	//结束格式：
	//\033[0m   //结束一定要有结束标志
	//
	//参数效果
	//总览
	//控制码	效果
	//\033[0m	关闭所有属性
	//\033[1m	设置字体高亮度
	//\033[2m	低亮（减弱）显示
	//\033[4m	下划线
	//\033[5m	闪烁
	//\033[7m	反显
	//\033[8m	消隐
	//\033[30m~\033[39m	字体颜色
	//\033[30m~\033[39m	背景颜色
	// 
	//单值控制码
	//不能与其他控制码联用
	//控制码	效果
	//\033[nA	光标上移n行
	//\033[nB	光标下移n行
	//\033[nC	光标右移n列
	//\033[nD	光标左移n列
	//\033[y; xH	设置光标位置（y行, x列）
	//\033[2J	清屏
	//\033[K	清除从光标到行尾的内容
	//\033[s	保存光标位置
	//\033[u	恢复光标位置
	//\033[? 25l	隐藏光标
	//\033[? 25h	显示光标
	// 
	//字体颜色
	//控制码	字体效果
	//\033[30m	黑色
	//\033[31m	红色
	//\033[32m	绿色
	//\033[33m	黄色
	//\033[34m	蓝色
	//\033[35m	紫色
	//\033[36m	浅蓝色
	//\033[37m	白色
	//\033[38m	无
	//\033[39m	无
	// 
	//背景颜色
	//控制码	背景效果
	//\033[40m	黑色
	//\033[41m	红色
	//\033[42m	绿色
	//\033[43m	黄色
	//\033[44m	蓝色
	//\033[45m	紫色
	//\033[46m	浅蓝色
	//\033[47m	白色
	//\033[48m	无
	//\033[49m	无

	//C语言代码
	//#include <stdio.h>
	printf("以下是测试文字：\n");
	printf("\033[0m默认文字\033[0m\n");
	printf("\033[1m高亮文字\033[0m\n");
	printf("\033[2m低亮文字\033[0m\n");
	printf("\033[3m无效文字\033[0m\n");
	printf("\033[4m下划线文字\033[0m\n");
	printf("\033[5m闪烁文字(无效)\033[0m\n");
	printf("\033[6m无效文字\033[0m\n");
	printf("\033[7m反显文字\033[0m\n");
	printf("\033[8m消隐文字(无效)\033[0m\n");

	printf("\n\033[31;1m字体颜色\033[0m测试文字\n");
	printf("\033[30m低亮黑色文字\033[0m\t\033[30;1m高亮黑色文字\033[0m\n");
	printf("\033[31m低亮红色文字\033[0m\t\033[31;1m高亮红色文字\033[0m\n");
	printf("\033[32m低亮绿色文字\033[0m\t\033[32;1m高亮绿色文字\033[0m\n");
	printf("\033[33m低亮黄色文字\033[0m\t\033[33;1m高亮黄色文字\033[0m\n");
	printf("\033[34m低亮蓝色文字\033[0m\t\033[34;1m高亮蓝色文字\033[0m\n");
	printf("\033[35m低亮紫色文字\033[0m\t\033[35;1m高亮紫色文字\033[0m\n");
	printf("\033[36m低亮浅蓝文字\033[0m\t\033[36;1m高亮浅蓝文字\033[0m\n");
	printf("\033[37m低亮白色文字\033[0m\t\033[37;1m高亮白色文字\033[0m\n");
	printf("\033[38m测试文字\033[0m\n");
	printf("\033[39m测试文字\033[0m\n");

	printf("\n\033[31;1m背景颜色\033[0m测试文字\n");
	printf("\033[40m低亮文字黑色背景\033[0m\t\033[40;1m高亮文字黑色背景\033[0m\n");
	printf("\033[41m低亮文字红色背景\033[0m\t\033[41;1m高亮文字红色背景\033[0m\n");
	printf("\033[42m低亮文字绿色背景\033[0m\t\033[42;1m高亮文字绿色背景\033[0m\n");
	printf("\033[43m低亮文字黄色背景\033[0m\t\033[43;1m高亮文字黄色背景\033[0m\n");
	printf("\033[44m低亮文字蓝色背景\033[0m\t\033[44;1m高亮文字蓝色背景\033[0m\n");
	printf("\033[45m低亮文字紫色背景\033[0m\t\033[45;1m高亮文字紫色背景\033[0m\n");
	printf("\033[46m低亮文字浅蓝背景\033[0m\t\033[46;1m高亮文字浅蓝背景\033[0m\n");
	printf("\033[47m低亮文字白色背景\033[0m\t\033[47;1m高亮文字白色背景\033[0m\n");
	printf("\033[48m测试文字\033[0m\n");
	printf("\033[49m测试文字\033[0m\n");
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
