// stringTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;
void tt1();
void tt2();
void tt3();
void tt4();
void tt5();
void tt6();

int main()
{
    std::cout << "Hello World!\n";
	//tt1();
	//tt2();
	//tt3();
	//tt4();
	//tt5();
	tt6();
}



void tt1()
{
	std::string szLabel = "ip-192.1681.1.1.1-company-co_123_test-net-Net_1234_test";
	std::string strTIp = "ip-";
	std::string strTCompany = "-company-";
	std::string strTNet = "-net-";

	size_t sCompanny = szLabel.find("-company-");
	size_t sNet = szLabel.find("-net-");

	std::string szCCU = szLabel.substr(strTIp.size(), sCompanny - strTIp.size());
	std::string strCompany = szLabel.substr(sCompanny + strTCompany.size(), sNet - sCompanny - strTCompany.size());
	std::string strNet = szLabel.substr(sNet + strTNet.size());
}

void tt2()  //从末尾开始提取IP
{
	string tmp = "1.3.6.1.4.1.25506.2.67.1.1.2.1.4.634.1.4.192.168.11.254";
	size_t pos = string::npos;
	string::reverse_iterator it = tmp.rbegin();

	string ret = "";
	string ret2 = "";
	string ret3 = "";
	string ret4 = "";

	int i = 0;
	int i2 = 0;
	for (it = tmp.rbegin(); it != tmp.rend() && i < 4; ++it)
	{
		if (*it == '.')
		{
			++i;
		}
		++i2;
	}

	if (it == tmp.rend() || i < 4)
	{
		
	}

	int ii = std::distance(tmp.rbegin(), it);
	int ii2 = it - tmp.rbegin();
	ret = tmp.substr(tmp.length() - (it - tmp.rbegin()) + 1);
	ret2 = tmp.substr(tmp.length() - i2 + 1);
	ret3 = tmp.substr(tmp.length() - ii2 + 1);
	ret4.assign(it.base(), tmp.end());
	printf("ret:%s\n", ret.c_str());
}


void tt3()
{
	std::string str1 = "abc123 abc123";
	std::string str2 = "abc abc";
	std::string str3 = "";

	str3 = str1.replace(str1.find("123"), 2, "qazx");
	str3 = str2.replace(str2.find("123"), 2, "qazx");

	return;
}


void tt4()
{
	string str1 = "0";
	string str2 = "";

	long long l1 = atoll(str1.c_str());
	long long l2 = atoll(str2.c_str());
}

void tt5()
{
	string starttime = "2022-09-01 10:05:01";
	string endtime = "2022-11-15 23:59:59";
	int nYear = 0, nMonth, nDay, nHour, nMinuter, nSecond;
	int n = 0;
	if (endtime.compare(starttime) >= 0)
	{
		n = sscanf_s(starttime.c_str(), "%4d-%2d-%2d %d:%d:%d", &nYear, &nMonth, &nDay, &nHour, &nMinuter, &nSecond);
		n = sscanf_s(endtime.c_str(), "%4d-%2d-%2d %d:%d:%d", &nYear, &nMonth, &nDay, &nHour, &nMinuter, &nSecond);
	}
}

void tt6()
{
	//double do1 = -nan(ind);
	printf("-->%f %d\n", 1.0 / 1, 1);
	//printf("-->%f %d\n", 1.0 / 0, 1);
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
