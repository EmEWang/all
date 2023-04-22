

#include <iostream>
#include <string>
#include <map>
#include <winsock.h>

#include "ipmgminterface.h"

#include "chen\\TimeFace.h"
#include "mxcomlib\\MxUtil.h"

using namespace std;

int ConvertIpToInt(std::string ip);
unsigned long ConvertIpToULong(std::string ip);

void testModifyip();

int main()
{
    testModifyip();

    return 0;


    std::cout << "Hello World!\n";
    string time = chen::TimeFace::GetCurrent().ToString();
    string time2 = chen::TimeFace::GetCurrent().ToHttpGMTString();
    string time4 = chen::TimeFace::GetCurrent().ToUSAString();
    std::string szPath = CMxUtil::GetInstallPath();


    string strCo = "Co_1";
    string strNet = "Net_1";
    string strNet3 = "Net_3";
    string strSubNet = "103.219.185.16/28";

    string strJson;

    std::map<int, int> map_int;
    std::map<int, int>::iterator it_int = map_int.find(1);


    unsigned int l1 = 4294967280;

    string strIp = "192.168.10.199";

	unsigned long lIp = inet_addr(strIp.c_str());

    int iii = (int)lIp;


    cout << iii << endl; 


    cout << ConvertIpToInt("192.168.10.199") << endl;
    cout << ConvertIpToULong("192.168.10.199") << endl;
    cout << ConvertIpToInt("255.255.255.240") << endl;
    cout << ConvertIpToULong("255.255.255.240") << endl;



    InitData();
    //strJson = GetGroupSubNetJson(strCo, strNet,1);
    //cout << "GetGroupSubNetJson" << endl << strJson << endl;

    //strJson = GetIPJson(strCo, strNet, "103.219.185.16/28", 1);
    //strJson = GetIPJson(strCo, strNet, "192.168.2.0/24", 1);
    //strJson = GetIPJson(strCo, strNet, "192.168.2.0/24", 1);
   // cout << "GetIPJson" << endl << strJson << endl;

   // ModifyIp(strCo, strNet, "192.168.2.1", 2);

	//strJson = GetIPJson(strCo, strNet, "192.168.2.0/24", 1);
	//cout << "GetIPJson" << endl << strJson << endl;

	//strJson = GetUnTrustIPCoJson(strCo);
	//cout << "GetUnTrustIPCoJson" << endl << strJson << endl;


 //   ModifySubNet(strCo, strNet3, "192.168.1.0/24", 0);
	//strJson = GetGroupSubNetJson(strCo, strNet3, 1);
	//cout << "GetGroupSubNetJson" << endl << strJson << endl;

	//ModifySubNet(strCo, strNet3, "192.168.2.0/24", 0);
	//strJson = GetGroupSubNetJson(strCo, strNet3, 1);
	//cout << "GetGroupSubNetJson" << endl << strJson << endl;

	//list<string> iplst;
	//iplst.push_back("192.168.2.1");
	//iplst.push_back("192.168.2.2");
	//NotifyIpTrust(strCo, strNet3, iplst);

	
    strJson = GetIPJson("Co_1", "Net.3", "192.168.2.0/24", 1);
    cout << "GetIPJson" << endl << strJson << endl;

    //ModifyIp(strCo, strNet, "103.219.185.23", 1);
    //ModifyIp(strCo, strNet, "103.219.185.24", 0);
    //ModifyIp(strCo, strNet, "103.219.185.25", 2);

    //ModifyNetGroup(strCo, strNet, "group1", 1);


    //system("pause");
}

void ipCount()
{
	int iMask = 16777215;
	int iIp = 174272;

	int iCount = (~iMask | iIp) - (iMask & iIp);

	std::cout << "ipcont:" << iCount << endl;
}

int ConvertIpToInt(std::string ip) {
	string strIp = "192.168.10.199";
	unsigned long lIp = inet_addr(ip.c_str());
    return lIp;
}
unsigned long ConvertIpToULong(std::string ip) {
	string strIp = "192.168.10.199";
	unsigned long lIp = inet_addr(ip.c_str());
	return lIp;
}


void testModifyip()
{
    printf("111\n");
    InitData();
    ModifyIp("Co_1", "Net.11", "10.0.10.111;10.0.10.112;10.0.10.113;10.0.10.114;10.0.10.115;10.0.10.116", 2, 2);
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
