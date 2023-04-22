// winTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include  <afxtempl.h>
//#define _AFXDLL

//CMap 可以便删除边添加边修改
void testCMap();
//CString也是以0为结束符的字符串
void testCString();
//CList 列表 内部则用了双向链表
void testCList();

//注册表
void testRegedit();

int main()
{
	//testCMap();
	//testCString();
	//testCList();
	testRegedit();
    std::cout << "Hello World!\n";
}


CMap<int, int, CString, CString> map_1;
void testCMapInit()
{
	map_1.SetAt(1, "aaa");
	map_1.SetAt(2, "bbb");
	map_1.SetAt(3, "ccc");
	map_1.SetAt(4, "ddd");
}

void testCMapTraverse()
{
	POSITION pos = map_1.GetStartPosition();
	unsigned int uindex = 0;
	while (pos)
	{
		int index;
		CString value;
		map_1.GetNextAssoc(pos, index, value);
		printf("[index]%u[%d--%ws]\n", ++uindex, index, value.GetBuffer());
	}
}

// CMap可以边遍历边插入数据
void testCMapTraverseDel()
{
	POSITION pos = map_1.GetStartPosition();
	unsigned int uindex = 0;
	while (pos)
	{
		int index;
		CString value;
		map_1.GetNextAssoc(pos, index, value);
		if (index ==2)
		{
			map_1.RemoveKey(index);
			map_1.SetAt(5, "eee");
		}
		if (index == 3)
		{
			map_1.RemoveKey(index);
			map_1.SetAt(6, "fff");
		}
	}
}

void testCMap()
{
	testCMapInit();
	testCMapTraverseDel();
	testCMapTraverse();
}



CString str_1;
CString str_2;
void testCStringInit()
{
	char ch[100] = { 0 };
	ch[0] = 0x31;
	ch[1] = 0x32;
	ch[2] = 0x33;
	ch[3] = 0x34;
	ch[4] = 0x0;
	ch[5] = 0x35;


	str_1 = "12345";
	str_2 = ch;
}


void testCStringPrint()
{
	printf("[str_1][len]%d[content]%ls\n", str_1.GetLength(), str_1.GetBuffer());
	printf("[str_2][len]%d[content]%ls\n", str_2.GetLength(), str_2.GetBuffer());
}

void testCString()
{
	testCStringInit();
	testCStringPrint();
}


void testCList()
{
	//CList
	//是一个模板类，其实就是一个双向链表。支持多个对象的顺序列表，可以同时顺序或者值访问对象成员。
	//头文件名不可少 类定义在Afxtempl.h 头文件中，因此在使用该类时，需要加这个头文件名。
	//template< class TYPE, class ARG_TYPE >class CList : public CObject
	//TYPE 要存储的对象类型 ARG_TYPE 在列表中用于引用对象的类型 若不定义第二个参数 其默认是第一种类型的引用
	//下面看一个例子：
	//CList<CString, CString&> list;//链表对象1
	//CList<CString, CString> list2;//链表对象2
	//这里的第一个参数CString是实例化的类型，第二个参数是类的成员函数的参数的调用形式，通常是类型　引用，当然也可以是对象，而不是引用。
	//GetHeadPosition / GetTailPosition / GetNext / GetPrev
	//
	//POSITION GetHeadPosition() const;
	//返回值：返回列表中头元素的位置。如果列表为空返回NULL；返回值POSITION可用于迭代或者对象指针的检索。
	//POSITION GetTailPosition() const;
	//获得尾部元素的位置，如果列表为空，返回NULL。
	//TYPE GetNext(POSITION & rPosition) const;
	//如果列表为常量 返回值为头元素的拷贝 如果类表不为常量 返回头元素的引用
	//TYPE 列表中对象类型
	//rPosition 先前的GetNext，GetHeadPosition函数返回的一个位置值引用，或其他成员函数调用返回的引用。
	// 获得由rPosition标志的列表元素，然后设置rPosition 为列表下一个入口的POSITION值
	//迭代过程可用此循环
	//Position = m_list.GetHeadPosition();
	//do
	//{
	//	lpConnect = m_list.GetNext(Position);
	//	lpConnect->lpInterface->Draw(hDC);
	//} while (Position);
	//GetPrev（）
	//同GetNext，但返回列表中前一个位置引用

	CList<int*> listint;
	listint.AddTail(new int(1));
	listint.AddTail(new int(2));
	listint.AddTail(new int(3));
	listint.AddTail(new int(4));
	listint.AddTail(new int(5));

	POSITION pos = listint.GetHeadPosition();
	
	int index = 0;
	while (pos)
	{
		++index;
		POSITION lpos = pos;
		int* p1 = listint.GetNext(pos);
		printf("%d -- %d\n", index, *p1);

		if (*p1 % 2 )
		{
			listint.RemoveAt(lpos);
			delete p1;
		}
	}

	CList<int*> listint2;
	listint2.AddTail(&listint);
	listint.RemoveAll();

	pos = listint2.GetHeadPosition();
	index = 0;
	while (pos)
	{
		++index;
		POSITION lpos = pos;
		int* p1 = listint2.GetNext(pos);
		printf("%d -- %d\n", index, *p1);
	}
}


//无法看到RegEdit中的某些HKEY_LOCAL_MACHINE条目
//64位版本的Windows通过“Windows on Windows”（WoW）子系统模拟32位功能。在注册表中，出于兼容性原因，他们将32位密钥移至特殊的子密钥。
//钥匙将在：HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node。
//这是文件系统重定向器的注册表模拟，它将system32映射到SysWOW64。
//https://learn.microsoft.com/zh-cn/windows/win32/winprog64/registry-redirector?redirectedfrom=MSDN
void testRegedit()
{
	HKEY hKey = NULL;
	HKEY hKey2 = NULL;
	LONG lRet = 111;

	bool bSources = false;
	//lRet = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources", 0, KEY_QUERY_VALUE, &hKey);
	
	lRet = RegOpenKeyEx(                                          //打开注册表树的某个节点  左边面板
		HKEY_LOCAL_MACHINE,         // handle to open key         
		"Hardware\\Description\\System\\CentralProcessor\\0",  // subkey name
		0,   // reserved
		KEY_QUERY_VALUE, // security access mask
		&hKey    // handle to open key
	);
	if (lRet == ERROR_SUCCESS)                                          // 取一个值
	{
		TCHAR tchData[64];
		DWORD dwSize = sizeof(tchData);
		lRet = RegQueryValueEx(                                  //打开注册表的某个具体键值 右边面板
			hKey,            // handle to key
			"ProcessorNameString",  // value name
			NULL,   // reserved
			NULL,       // type buffer
			(LPBYTE)tchData,        // data buffer
			&dwSize      // size of data buffer
		);
		if (lRet == ERROR_SUCCESS)
		{
			printf("\n CPU INFO:");
			printf("%s\n", tchData);
		}
		//以下是失败的内容
		else
		{
			printf("\nCPU INFO:");
			printf("UNKNOWN\n");
		}
	}
	if (lRet == ERROR_SUCCESS) {                                      // 遍历
		// TODO: 
		DWORD dwIndex = 0;
		while (1) {
			char szValueName[512] = { 0 };
			DWORD dwSizeValue = sizeof(szValueName) - 1;

			char szVal[512] = { 0 };
			DWORD len = 512;

			lRet = RegEnumValue(hKey, dwIndex, szValueName, &dwSizeValue, NULL, NULL, (LPBYTE)szVal, &len);              //dwSizeValue 为szValueName长度  根据 (LPBYTE) 遍历 len为szVal长度

			puts("call RegEnumValue");
			if (lRet != ERROR_SUCCESS)
			{
				break;
			}

			//if(strstr(szVal, "Oracle") ==NULL)
			{
				bSources = true;
				//sprintf(pt, "%s=%s", szValueName, szValueName);
				//pt += 2 * strlen(szValueName) + 2;

			}

			dwIndex++;
		}
		RegCloseKey(hKey);
	}


	//lRet = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\OpenVPN", 0, KEY_QUERY_VALUE, &hKey);
	lRet = RegOpenKeyEx(                                          //打开注册表树的某个节点  左边面板
		HKEY_LOCAL_MACHINE,         // handle to open key
		"SOFTWARE\\Kingsoft\\Office\\6.0\\Common",  // subkey name
		0,   // reserved
		KEY_QUERY_VALUE, // security access mask
		&hKey2    // handle to open key
	);
	if (lRet != ERROR_SUCCESS)
	{
		char szError[256];
		//DWORD dwError = GetLastError();
		DWORD dwError = lRet;
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM,                          //查找某个具体值的描述
			NULL,
			dwError,
			0,
			szError,
			sizeof(szError),
			NULL);

		int i = 1;
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
