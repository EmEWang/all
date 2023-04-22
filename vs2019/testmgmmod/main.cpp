

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

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
