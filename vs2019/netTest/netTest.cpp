// netTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>

#ifdef WIN32
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#pragma comment(lib, "D:\\Code\\webwork_new\\bin\\ServerData.lib")
#pragma comment(lib, "D:\\Code\\base\\lib\\win\\libchen.lib")
#else

#endif // WIN32

#include "D:\\Code\\webwork_new\\ServerData\\ipmgm\\SSubNet.h"


#pragma warning(suppress : 4996)
using namespace std;


void ipCount(int ip = 0, int mask = 0);
void ipCount2(const std::string &ip, const std::string &mask);
bool netInit();
bool netClean();
bool sock_client(const std::string &ip = "127.0.0.1", int port = 6660, int af = AF_INET, int type = SOCK_STREAM, int protocol = 0);
bool sock_server(const std::string& ip = "127.0.0.1", int port = 6660, int af = AF_INET, int type = SOCK_STREAM, int protocol = 0);

void testNetList();



int main()
{
	//netInit();
	//ipCount(3232236075, 4294967040);
	//sock_server();
	//ipCount2("10.115.128.12", "255.255.255.252");

	testNetList();

    std::cout << "Hello World!\n";

	system("pause");
	return 0;
}

void ip()
{
	;
}



void ipCount(int ip, int mask)
{
	int iMask = 16777215;
	int iIp = 174272;
	int iCount = 0;

	if (ip == 0 && mask == 0)
	{
		iCount = (~iMask | iIp) - (iMask & iIp);
	}
	else
	{
		iCount = (~mask | ip) - (mask & ip);
	}
	std::cout << "ipcont:" << iCount << endl;
}

void ipCount2(const std::string &ip, const std::string &mask)
{
	unsigned long lIp = inet_addr(ip.c_str());
	unsigned long lMask = inet_addr(mask.c_str());
	unsigned int lm = ntohl(lMask);
	unsigned int lp = ntohl(lIp);

	std::cout << "[ip_min]" << lp << "[ip_max]" << ((~lm) | lp) << std::endl;
}


bool netInit()
{
	int nRet = 0;
#ifdef WIN32
	WORD version;
	WSADATA wsaD;
	version = MAKEWORD(1,1);
	nRet = WSAStartup(version, &wsaD);
	if (!nRet)
	{
		printf("netInit success\n");
	}
	else
	{
		printf("netInit fail\n");
		return false;
	}
#else
#endif // WIN32
	
	return true;
}

bool netClean()
{
	int nRet = 0;
#ifdef WIN32
	nRet = WSACleanup();
	if (!nRet)
	{
		printf("netClean success\n");
	}
	else
	{
		printf("netClean fail\n");
		return false;
	}
#endif // WIN32
	
	return true;
}

bool sock_client(const std::string& ip, int port, int af, int type, int protocol)
{
	int nRet = 0;
#ifdef WIN32
	SOCKET sc = socket(af, type, protocol);
	SOCKADDR_IN addr_in;
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	addr_in.sin_family = af;
	//addr_in.sin_port = htons(port);
	addr_in.sin_port = port;
	nRet = connect(sc, (SOCKADDR*)&addr_in, sizeof(addr_in));
	if (!nRet)
	{
		printf("connect success\n");
	}
	else
	{
		printf("connect fail\n");
		return false;
	}

	char temp[100];
	char temp2[100] = "baby server!!";

	int len = 1;
	while (len)
	{
		recv(sc, temp, 100, 0);
		printf("[recv]%s\n", temp);

		scanf("%s", temp2);
		len = send(sc, temp2, strlen(temp2)+1, 0);
	}

	
	closesocket(sc);
#endif // WIN32

	
	return true;
}

bool sock_server(const std::string& ip, int port, int af, int type, int protocol)
{
	int nRet = 0;
	SOCKET sc = socket(af, type, protocol);
	SOCKADDR_IN addr_in;
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr_in.sin_family = af;
	addr_in.sin_port = port;	
	nRet = bind(sc, (SOCKADDR*)&addr_in, sizeof(addr_in));
	if (!nRet)
	{
		printf("bind success\n");
	}
	else
	{
		printf("bind fail\n");
		return false;
	}

	nRet = listen(sc, 10);
	int len = sizeof(SOCKADDR_IN);
	int len2 = 0;
	SOCKET sc_ac;
	while (1)
	{
		len = sizeof(SOCKADDR_IN);
		SOCKADDR_IN addr_cl;
		sc_ac = accept(sc, ((SOCKADDR*)&addr_cl), &len);
		int reuse = 0x0;
		//int ll = setsockopt(sc_ac, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int));
		char temp[100];
		sprintf(temp, "hello %s", inet_ntoa(addr_cl.sin_addr));
		len = send(sc_ac, temp, strlen(temp) + 1, 0);
		char temp2[100];
		len = 1;
		while (len>0)
		{
			len = recv(sc_ac, temp2, 100, 0);
			printf("[recv]%s\n", temp2);
			sprintf(temp, "receive %s", inet_ntoa(addr_cl.sin_addr));
			if (len >0)
			{
				len2 = send(sc_ac, temp, strlen(temp) + 1, 0);
			}
			
		}

		//printf("[recv]%s\n", temp2);
		//closesocket(sc_ac);
		printf("[close]%s\n", temp2);
	}
	return true;
}

void testNetList()
{
	CSSubNet net;
	net.SetSubSet("10.0.6.0", "255.255.255.0");
	std::list<std::string> netlist;
	net.GetIpList(netlist);

	int i = 0;
	for (std::list<std::string>::iterator it = netlist.begin(); it != netlist.end(); ++it)
	{
		std::cout << ++i << " " << *it << std::endl;
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
