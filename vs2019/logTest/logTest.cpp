// logTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "DebugLog.h"
using namespace _mxcomm;
//#pragma comment(lib, "Rpcrt4.lib") 

using namespace std;

#define  IPCTRL				"ipctrl"

void tt1();


int main()
{
    tt1();
    std::cout << "Hello World!\n";
}


void tt1()
{
    //m_szFileDir:D:\JianKongYi\Server/middle/log/ LogLvel:10
    CDebugLog::WriteTimeFmtLog("tt1.log", CDebugLog::CRITICALOG, (char*)"CIpMgmSearch::DeleteUnExistIp IP=%s,mac:%s", "192.168.1.1", "aa.bb.cc.dd.ee.ff");

    cout << "func:" << __FUNCTION__ << endl;
    CDebugLog::WriteTimeFmtLog("tt1.log", CDebugLog::CRITICALOG, (char*)"func:%s", __FUNCTION__);

    CDebugLog::WriteTimeFmtLog("tt1.log", CDebugLog::CRITICALOG, (char*)"msg:%s", IPCTRL);

    cout << __FUNCTION__ << endl;

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
