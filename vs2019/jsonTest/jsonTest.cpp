// jsonTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <fstream>

#include "json.h"

using namespace std;

void parseTest(const string &file);
void parseTest2(const string& file);
void parseTest3(const string& file);
void parseTest4(const string& file);
void Init2(std::string strFile);
void MakeJson();
void MakeJson2();
string MakeScanSubnetJson(int nNum);
void ParseScanSubnetJson(string jStr);
void validJson(const string &strJ = "");

void makeJsonZero();
void makeJsonValueInValue();    //value = value  and  value = abc   output same

void testtype();

std::string strj3 = "{\
\"sa\":\"aaa\",\
\"sb\" : [\
{ \"sb_a\":\"sb_aaa\",\
\"sb_b\" : \"sb_bbb\"\
},\
{ \"sb_a\":\"sb_aaaaa\",\
  \"sb_b\" : \"sb_bbbbbb\"\
}\
] ,\
\"sc\":\"ccc\"\
}";


std::string strj4 = "\
{\"subnet\": [{\"IIp\":3232237574, \"IMask\" : 4294967040, \"SubNetId\" : \"192.168.8.0/24\", \"SubnetIp\" : \"192.168.8.6\", \"SubnetMask\" : \"255.255.255.0\", \"ip\" : \"192.168.8.6\", \"label\" : \"销售部门子网1\", \"manage\" : 1, \"mask\" : \"255.255.255.0\", \"new\" : 1, \"state\" : 0}] , \"ts\" : [{\"id\":\"1.TS.1\", \"mx_fixtsserver\" : \"ACD019F6-699B-4284-AAD4-7BBC946B6EC2\", \"mxlabel\" : \"本机容器\"}] , \"company\" : \"Co_1\", \"network\" : \"Net.2\"}\
";


std::string strj5 = " {\"subnet\": [], \"ts\": [{\"ccuid\": \"Co_1_7\", \"id\": \"1.TS.1\", \"mxGuid\": \"6eaa30fb - ba15 - 4372 - b537 - 4392afa81eba\", \"mx_fixtsserver\": \"6eaa30fb - ba15 - 4372 - b537 - 4392afa81eba\", \"mxlabel\": \"DOIM - 1\"}], \"company\": \"Co_1\", \"network\": \"Net.1\"}";

int main()
{
	//parseTest2("dbInfo.json");
	//Init2("dbInfo.json");

	//MakeJson();
	//MakeJson2();

	//parseTest3(strj3);
	//parseTest4(strj4);

	//cout << MakeScanSubnetJson(0) << endl << endl;
	//ParseScanSubnetJson(MakeScanSubnetJson(0));
	//cout << MakeScanSubnetJson(3) << endl << endl;
	//ParseScanSubnetJson(MakeScanSubnetJson(3));
    //system("pause");



	//ParseScanSubnetJson(strj5);

	//validJson(strj3);
	//validJson("{\"aa\":\"b\"}");

	//makeJsonZero();

	//makeJsonValueInValue();
	testtype();
}


void makeJsonZero()
{
	string strJson;
	Json::Value jRoot;
	jRoot["v1"] = 1111;
	jRoot["v2"] = "xxxx";
	jRoot["v3"].resize(0);



	std::cout << jRoot.toStyledString() << std::endl;
}

void makeJsonValueInValue()
{
	Json::Value v1;
	Json::Value v11("1_111");
	Json::Value v12(333);
	v1["data1"] = v11;
	v1["data2"] = "1_222";
	v1["data3"] = v12;
	v1["data4"] = 333;

	std::cout << v1.toStyledString() << std::endl;
}


void parseTest(const string& file)
{
	//string strFile = "test.json";
	string strFile = file;
	ifstream jsonfile(strFile, fstream::in);
	if (!jsonfile.is_open())
	{
		std::cout << "open file error" << endl;
		return ;
	}
	Json::Reader jRead;
	Json::Value jRoot;
	if (jRead.parse(jsonfile, jRoot))
	{
		string v1_name;
		cout << "v1_name:" << jRoot["v1_name"] << endl;
		Json::Value v2 = jRoot["v2"];
		cout << "v2_name:" << v2["v2_name"] << endl;
		Json::Value v3 = jRoot["v3"];
		cout << "v3_name:" << v2["v2_name"] << "name:" << v3["name"] << "age:" << v3["age"] << endl;
	}
}

void parseTest2(const string& file)
{
	//string strFile = "test.json";
	string strFile = file;
	ifstream jsonfile(strFile, fstream::in);
	if (!jsonfile.is_open())
	{
		std::cout << "open file error" << endl;
		return;
	}

	Json::Reader jReader;
	Json::Value jRoot;
	if (jReader.parse(jsonfile, jRoot))
	{
		Json::Value jmodule = jRoot["module"];
		for (size_t i = 0; i < jmodule.size(); i++)
		{
			cout << "moudle" << endl;
			string name = jmodule[i]["name"].asString();
			cout << "    " << name << endl;
			Json::Value jtree = jmodule[i]["tree"];
			cout << "    "  << "tree" << endl;
			for (size_t i = 0; i < jtree.size(); i++)
			{
				string name = jtree[i]["name"].asString();
				string ip   = jtree[i]["ip"].asString();
				string port = jtree[i]["port"].asString();

				cout << "    " << "    " << name << ":" << ip << ":" << port << endl;
			}

			Json::Value jtable = jmodule[i]["table"];
			cout << "    " << "table" << endl;
			for (size_t i = 0; i < jtable.size(); i++)
			{
				string name = jtable[i]["name"].asString();
				string ip = jtable[i]["ip"].asString();
				string port = jtable[i]["port"].asString();

				cout << "    " << "    " << name << ":" << ip << ":" << port << endl;
			}

			Json::Value jmq = jmodule[i]["mq"];
			cout << "    " << "mq" << endl;
			for (size_t i = 0; i < jmq.size(); i++)
			{
				string name = jmq[i]["name"].asString();
				string ip = jmq[i]["ip"].asString();
				string port = jmq[i]["port"].asString();

				cout << "    " << "    " << name << ":" << ip << ":" << port << endl;
			}
		}
		
	}
}

void parseTest3(const string& file)
{
	std::string jsonfile = file;
	Json::Reader jReader;
	Json::Value jRoot;
	if (jReader.parse(jsonfile, jRoot))
	{
		Json::Value jmodule = jRoot["sb"];
		for (size_t i = 0; i < jmodule.size(); i++)
		{
			string name = jmodule[i]["sb_a"].asString();
			cout << "sb:sb_a:" << name << endl;

			//类型出错 解析直接崩 需要判断
			if (jmodule[i]["sb_a"].isInt())
			{
				int name2 = jmodule[i]["sb_a"].asInt();
				//int name2 = jmodule[i]["sb_a"].asInt();
				cout << "sb:sb_a:" << name2 << endl;
			}

			if (jmodule[i]["sb_a"].isString())
			{
				std::string name2 = jmodule[i]["sb_a"].asString();
				cout << "sb:sb_a:" << name2 << endl;
			}			
		}

		//Json::UInt;
		std::string szTs = jmodule[(Json::UInt)0]["sb_a"].asString();
		int ni = 0;
		szTs = jmodule[ni]["sb_a"].asString();

		//节点不存在 返回 null 和 0 不出错
		cout << "sb:sb_noexist:" << jRoot["sb_noexist"]  << endl;
		cout << "sb:sb_noexistsize:" << jRoot["sb_noexist"].size() << endl;

		// 0 不行 1可以
		//cout << "sb:sb_a:" << jmodule[0]["sb_a"].asString() <<  endl;

		int i = 0;
		cout << "sb:sb_a:" << jmodule[i]["sb_a"].asString() << endl;
	}
}

void parseTest4(const string& file)
{
	std::string jsonfile = file;
	Json::Reader jReader;
	Json::Value jRoot;
	int nSubNet = 0;
	bool bJson = false;

	std::string m_strCompany;
	std::string m_strNet;

	std::vector<std::string> subnetIds;
	std::vector<std::string> subnetIps;
	std::vector<std::string> subnetMasks;

	if (jReader.parse(jsonfile, jRoot))
	{
		Json::Value jSubnet = jRoot["subnet"];
		for (size_t i = 0; i < jSubnet.size(); i++)
		{
			std::string id = jSubnet[i]["SubNetId"].asString();
			std::string ip = jSubnet[i]["SubnetIp"].asString();
			std::string mask = jSubnet[i]["SubnetMask"].asString();
			subnetIds.push_back(id);
			subnetIps.push_back(ip);
			subnetMasks.push_back(mask);
			++nSubNet;

			std::cout << "FileterSubNetIp %d subnetid:%s subnetip:%s subnetmask:%s" << nSubNet << id << ip << mask << endl;
			//printf((char*)"FileterSubNetIp %d subnetid:%s subnetip:%s subnetmask:%s", nSubNet, id, ip, mask);
		}

		m_strCompany = jRoot["company"].asString();
		m_strNet = jRoot["network"].asString();
	}
	else
	{
		std::cout << "FileterSubNetIp strIpScanJson parse error:%s" <<  endl;
		return;
	}
}
void Init2(std::string strFile)
{


	if (strFile.empty()) {
		return;
	}
	ifstream ifs(strFile, fstream::in);
	if (ifs)
	{
		cout << "open " << strFile << " success" << endl;
	}
	else
	{
		cout << "open " << strFile << " failed" << endl;
		return;
	}
	Json::Reader jReader;
	Json::Value jRoot;

	if (!jReader.parse(ifs, jRoot))
	{
		ifs.close();
		return;
	}
	ifs.close();
	cout << jRoot.size() << endl;
	Json::Value jModule = jRoot["module"];
	cout << jModule.size() << endl;
	for (size_t i = 0; i < jModule.size(); i++)
	{
		if (!jModule[i].isMember("name"))
			continue;
		std::string strMoudle = jModule[i]["name"].asString();

		if (jModule[i].isMember("tree"))
		{
			Json::Value jTree = jModule[i]["tree"];
			std::string strTree = "Tree";
			for (size_t i = 0; i < jTree.size(); i++)
			{
				if (jTree[i].isMember("name") && jTree[i].isMember("ip") && jTree[i].isMember("port"))
				{
					string name = jTree[i]["name"].asString();					
					string ip = jTree[i]["ip"].asString();
					string pp = jTree[i]["port"].asString();
					//int port = jTree[i]["port"].asUInt();
					int port = atoi(jTree[i]["port"].asString().c_str());

					cout << "    " << "    " << name << ":" << ip << ":" << port << endl;
					//CDbIpNode node(port, ip, strMoudle, strTree, name);
					//g_mapDbInfo2[node.MakeKey()] = node;
				}
				else
				{
					return;
				}
			}
		}

		if (jModule[i].isMember("table"))
		{
			Json::Value jTable = jModule[i]["table"];
			std::string strTree = "table";
			for (size_t i = 0; i < jTable.size(); i++)
			{
				if (jTable[i].isMember("name") && jTable[i].isMember("ip") && jTable[i].isMember("port"))
				{
					string name = jTable[i]["name"].asString();
					string ip = jTable[i]["ip"].asString();
					int port = atoi(jTable[i]["port"].asString().c_str());

					cout << "    " << "    " << name << ":" << ip << ":" << port << endl;
					//CDbIpNode node(port, ip, strMoudle, strTree, name);
					//g_mapDbInfo2[node.MakeKey()] = node;
				}
				else
				{
					return;
				}
			}
		}


		if (jModule[i].isMember("mq"))
		{
			Json::Value jMq = jModule[i]["mq"];
			std::string strTree = "mq";
			for (size_t i = 0; i < jMq.size(); i++)
			{
				if (jMq[i].isMember("name") && jMq[i].isMember("ip") && jMq[i].isMember("port"))
				{
					string name = jMq[i]["name"].asString();
					string ip = jMq[i]["ip"].asString();
					int port = atoi(jMq[i]["port"].asString().c_str());

					cout << "    " << "    " << name << ":" << ip << ":" << port << endl;
					//CDbIpNode node(port, ip, strMoudle, strTree, name);
					//g_mapDbInfo2[node.MakeKey()] = node;
				}
				else
				{
					return;
				}
			}
		}
	}
	//g_bInit = true;
}

void MakeJson()
{
	string strJson;
	Json::Value jRoot;
	Json::Value jNode;
	jRoot["v1"] = 111;
	jRoot["v2"] = true;
	jRoot["v3"] = 22.22;
	jNode["v11"] = "v_11";
	jNode["v12"] = "v_12";
	jNode["v13"] = "v_13";
	jRoot["v4"] = jNode;

	std::cout << jRoot.toStyledString() << std::endl;

}

void MakeJson2()
{
	string strJson;
	Json::Value jRoot;
	Json::Value jNode1, jNode2, jNode3 ;
	jRoot["v1"] = "v_1";
	jRoot["v2"] = "v_2";
	jRoot["v3"] = "v_3";
	jNode1["v11"] = "v_11";
	jNode2["v12"] = "v_12";
	jNode3["v13"] = "v_13";
	jRoot["v4"].append(jNode1) ;
	jRoot["v4"].append(jNode2);
	jRoot["v4"].append(jNode3);
	

	std::cout << jRoot.toStyledString() << std::endl;

}

string MakeScanSubnetJson(int nNum)
{
	Json::Value jRoot;
	jRoot["company"] = "Co_1";
	jRoot["network"] = "Net_1";

	if (nNum == 0)
	{
		Json::Value jSubnet;
		jRoot["subnet"]="";
	}

	for (int i=0;  i < nNum; ++i)
	{
		Json::Value jSubnet;
		jSubnet["SubNetId"] = i;
		jSubnet["SubnetIp"] = i;
		jSubnet["SubnetMask"] = i;

		jRoot["subnet"].append(jSubnet);
	}

	for (int i = 0; i < 2; ++i)
	{
		Json::Value jTs;
		jTs["TsId"] = i;
		jTs["TsIndex"] = i;
		jRoot["ts"].append(jTs);
	}

	return jRoot.toStyledString();
}

void ParseScanSubnetJson(string jStr)
{
	Json::Value jRoot;
	Json::Reader jReader;

	jReader.parse(jStr, jRoot);

	cout << "[company]" << jRoot["company"].asString() << endl;
	cout << "[network]" << jRoot["network"].asString() << endl;

	Json::Value jTs = jRoot["ts"];
	cout << "[ts]size:" << jTs.size() << endl;
	for (int i = 0; i < jTs.size(); i++)
	{
		cout << "[Ts]" << i << endl;
		cout << "[TsId]" << jTs[i]["TsId"].asInt() << endl;
		cout << "[TsIndex]" << jTs[i]["TsIndex"].asInt() << endl;
	}

	Json::Value jSubnet = jRoot["subnet"];
	cout << "[subnet]size:" << jSubnet.size() << endl;
	for (int i = 0; i < jSubnet.size(); i++)
	{
		cout << "[subnet]" << i << endl;
		cout << "[SubNetId]" << jSubnet[i]["SubNetId"].asInt() << endl;
		cout << "[SubnetIp]" << jSubnet[i]["SubnetIp"].asInt() << endl;
		cout << "[SubnetMask]" << jSubnet[i]["SubnetMask"].asInt() << endl;
	}
}


void validJson(const string& strJ )
{
	Json::Value jRoot;
	Json::Reader jReader;

	if (jReader.parse(strJ, jRoot))
	{
		cout << "parse success" << endl;
	}
	else
	{
		cout << "parse failed" << endl;
		cout << jReader.getFormatedErrorMessages() << endl;
	}
}


void testidouble(double d)
{
	//C和C++11标准提供了类似于isnan、isfinite、isinf、isnormal、fpclassify分别用于判断是非数(NaN)值、有限制、无穷值、正常数值等。
	//isnan
	//NAN
	//Not - A - Number(constant)
	//isfinite
	//Is finite value(macro)
	//isinf
	//Is infinity(macro / function)
	//isnormal
	//Is normal(macro / function)
	//fpclassify
	//Classify floating - point value(macro / function)
	//C2668 “fpclassify”: 对重载函数的调用不明确    注意对整数没有意义 如果一定要使用 需要强制转化为double 如(double)(__ia)
	//注意:对整数使用isnan是没有意义的。 isnan( integer )将始终返回false，因此启用了优化的编译器应将整个调用替换为false。
	if (std::isnan(d))
	{
		printf("isnan  %f\n", d);
	}
	if (std::isinf(d))
	{
		printf("isinf  %f\n", d);
	}
	if (std::isnormal(d))
	{
		printf("isnormal  %f\n", d);
	}
	if (std::isfinite(d))
	{
		printf("isfinite  %f\n", d);
	}
	if (std::fpclassify(d))
	{
		printf("fpclassify  %f\n", d);
	}
}

void testtype()
{
	Json::Value jRoot;
	jRoot["double"] = Json::Value(-1.000000000000000000000000000000000000000000000000000000000000001);

	double dd = 0.99999999999999999999999999999999999999999999999999;	
	double dd3 = 0.0;
	double dd4 = 0.0;
	double dd2, dd222;

	dd2 = dd3 / dd4;                     //-nan(ind)  不是个数字 既不大于0 也不小于等于0
	double dd2_1 = 1 / dd3;                     //inf         无穷大
	double dd2_2 = -1 / dd3;                     //-inf        -无穷大
	dd222 = dd3 / dd4;
	char ch[100];
	sprintf(ch, "%0.1f", dd);
	if (!(dd2 > 0) && !(dd2 <= 0))                     
	{
		puts("dd2");
	}

	if (dd2 < 0)
	{
		dd2 = 1;
	}

	if (dd2_1  >100)
	{
		puts("dd2_1");
	}
	if (dd2_1 <= 100)
	{
		puts("dd2_1 ~");
	}

	if (dd2_2 > 100)
	{
		puts("dd2_2");
	}
	if (dd2_2 <= 100)
	{
		puts("dd2_2 ~");
	}
	if (dd2 > 100 || dd2 < 0.01)
	{
		dd2 = 123;
	}

	puts("-----dd2");testidouble(dd2);
	puts("-----dd2_1");testidouble(dd2_1);
	puts("-----dd2_2"); testidouble(dd2_2);
	

	jRoot["double2"] = Json::Value(dd2);
	jRoot["double2_1"] = Json::Value(dd2_1);
	jRoot["double2_2"] = Json::Value(dd2_2);
	//printf(">>%s<<\n", jRoot.toStyledString());
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
