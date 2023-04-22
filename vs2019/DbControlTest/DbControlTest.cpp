// DbControlTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "DbControl.h"

int main()
{
    std::cout << "!!!!!!!!!!!! >>START<< !!!!!!!!!!!!\n";

    int nRet = 0;

    //getFromTreeDb("127.0.0.1", "ccubase", "test", "subtest");
    //setToTreeDb("127.0.0.1", "ccubase", "test", "subtest");

    //生成
    //init("127.0.0.1" , "newfile", "mainkey", "subkey");
    //readinit("127.0.0.1", "newfile", "mainkey", "subkey");
    //clear("127.0.0.1", "newfile", "mainkey", "subkey");

    
   //遍历
    //readinit("127.0.0.1", "ccubase", "ccubase", "subkey2");

    //testPath();



    //sendMq("127.0.0.1", "111_test");
	//testInsertExistSubkey("127.0.0.1", "ipctrl", "Co");


	//editint();
	//readint();
	//int iMask = 16777215;
	//int iIp = 174272;
	//int iCount = (~iMask | iIp) - (iMask & iIp);
	//std::cout << "ipcont:" << iCount << endl;


    //sendMq2("127.0.0.1", "111_test");
    //getMq2("127.0.0.1", "111_test");


    //CNetGroup ng;
    //nRet = CIpControlDb::GetSingleNetGroup("192.168.4.34", "jky", "Net.1", "group.1", &ng);

    //
    //testBableDB("127.0.0.1", "MXSE_Netflow", "192_168_6_155_2021_10_03_18_xxxxxxx_netflow_conversation");
    //testBableDB("127.0.0.1", "MXSE_Netflow", "192_168_6_155_2021_10_04_18_xxxxxxx_netflow_conversation");
    //testBableDB("127.0.0.1", "MXSE_Netflow", "192_168_6_155_2021_10_05_18_xxxxxxx_netflow_conversation");
   

    //test键是否存在
    //testKeyExist("10.0.12.95", "ccubase", "Co_1_44", "1.SD.1");
    //testKeyPropertyExist("192.168.6.235", "ipctrl", "Co", "Co_1\\Config\\timedTask\\1", "mx1network");
    //testKeyPropertyExist("192.168.6.235", "ipctrl", "Co", "Co_1\\Config\\timedTask\\1", "mx1netwxxx");

    //测试 tableDB
    //testTableDB("127.0.0.1", "MXSE", "1.SD.1.SubMonitor.Ping_", "_CREATETIME_");
    //testTableDB("127.0.0.1", "MXSE", "1.SD.1.SubMonitor.Ping_", "State");
    //testTableDB("127.0.0.1", "operator", "Co_1", "_FIELD_AUTOID_");

    //testTableDBInsert("127.0.0.1", "MXSE_Netflow", "192_168_6_155_2022_05_19_15Hour_t_netflow_conversation2");

    //sendMq3("127.0.0.1", "ipmgm", "ip-Co_1_8-company-Co_1-net-Net.11", "C:\\Users\\wangjingang\\Desktop\\123");
    //sendMq3("192.168.6.235", "ipmgm", "ip-Co_1_8-company-Co_1-net-Net.11", "C:\\Users\\wangjingang\\Desktop\\123");

    //ClearIP("127.0.0.1", "Co_1", "Net.66");
    //ClearIP("127.0.0.1", "Co_1", "Net.66");
    //ClearIP("10.0.12.181", "Co_1", "Net.36");
    //ClearIP("10.0.128.33", "Co_1", "Net.11");


    //ClearIPOnce("127.0.0.1", "Co_1", "Net.66");

	//ConfigTest();


    //string server;
    //string co;
    //string net;
    //int num;
    //Config(server, co, net, num);
    //StatisticsIPNet("127.0.0.1", "Co_1");
    //StatisticsIPNet(server, co, net);
    //ClearIP(server, co, net);
    //StatisticsIPNet("10.0.128.33", "Co_1");

    //SpecialCharacter("127.0.0.1", "Co_1", "Check");


    writeTreeDb("127.0.0.1", "ccubase", "test", "subtest");


    std::cout << "!!!!!!!!!!!! >>FINISH<< !!!!!!!!!!!!\n";

    system("pause");
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
