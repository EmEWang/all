#pragma once
#include "MxHandlePool.h"

#include "all.h"

class synDb
{
public:
	bool init();

	bool frush(All &all);

	bool modify();

	bool modifyip(string net,  string ip, string key, string value);

private:
	
	bool m_ignore;
};

bool synDb::frush(All& all)
{
	CMxHandleLoc loc;
	int nRet = loc.Treedb_Alloc("227.0.0.2", "ccubase", "testipctrl", "", ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_CreateMainKey Error!" << " strServer:" << endl;
		return false;
	};

	string subkey = "net";
	loc.Treedb_ReopenSubKey(subkey);
	list<string> nets;
	loc.Treedb_GetAllSubKeys(nets);
	for (list<string>::iterator it = nets.begin(); it != nets.end(); ++it)
	{
		string _net = *it;

		//group
		string group = "group";
		string grouppath = subkey + "\\" + _net + "\\" + group;

		nRet = loc.Treedb_ReopenSubKey(grouppath);
		list<string> lgroup;
		loc.Treedb_GetAllSubKeys(lgroup);
		for (list<string>::iterator it = lgroup.begin(); it != lgroup.end(); ++it)
		{
			string strgroup = *it;
			Group gp;
			loc.Treedb_ReopenSubKey(grouppath + "\\" + strgroup);
			gp.m_path = loc.Treedb_GetPropertyString("path", "");
			all.m_m_net[_net].m_m_group[strgroup] = gp;
		}


		//ip
		string ip = "ip";
		string ippath = subkey + "\\" + _net + "\\" + ip;
		nRet = loc.Treedb_ReopenSubKey(ippath);
		list<string> lip;
		loc.Treedb_GetAllSubKeys(lip);
		for (list<string>::iterator it = lip.begin(); it != lip.end(); ++it)
		{
			string strip = *it;
			Ip ipp;
			loc.Treedb_ReopenSubKey(ippath + "\\" + strip);
			ipp.m_ip = loc.Treedb_GetPropertyString("ip", "");
			ipp.m_port = loc.Treedb_GetPropertyString("port", "");
			all.m_m_net[_net].m_m_ip[strip] = ipp;
		}


		//subnet
		string subnet = "subnet";
		string subnetpath = subkey + "\\" + _net + "\\" + subnet;
		nRet = loc.Treedb_ReopenSubKey(subnetpath);
		list<string> lsubnet;
		loc.Treedb_GetAllSubKeys(lsubnet);
		for (list<string>::iterator it = lsubnet.begin(); it != lsubnet.end(); ++it)
		{
			string strsubnet = *it;
			SubNet subnett;
			loc.Treedb_ReopenSubKey(subnetpath + "\\" + strsubnet);
			subnett.m_parent = loc.Treedb_GetPropertyString("path", "");
			all.m_m_net[_net].m_m_subnet[strsubnet] = subnett;
		}

		//ts
		string ts = "ts";
		string tspath = subkey + "\\" + _net + "\\" + ts;
		nRet = loc.Treedb_ReopenSubKey(tspath);
		list<string> lts;
		loc.Treedb_GetAllSubKeys(lts);
		for (list<string>::iterator it = lts.begin(); it != lts.end(); ++it)
		{
			string strts = *it;
			Ts tss;
			loc.Treedb_ReopenSubKey(tspath + "\\" + strts);
			tss.m_name = loc.Treedb_GetPropertyString("name", "");
			all.m_m_net[_net].m_m_ts[strts] = tss;
		}
	}

	return true;
}

bool synDb::modify()
{
	return true;
}


bool synDb::init()
{
	CMxHandleLoc loc;
	int nRet = loc.Treedb_Alloc("127.0.0.1", "ccubase", "testipctrl", "", ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_CreateMainKey Error!" << " strServer:" << endl;
		return false;
	};

	string strnet = "net";

	string strnet1						= "net\\net1";
	string strnet1group					= "net\\net1\\group";
	string strnet1groupg1				= "net\\net1\\group\\g1";
	string strnet1groupg2				= "net\\net1\\group\\g2";
	string strnet1groupg3				= "net\\net1\\group\\g3";
	string strnet1groupg4				= "net\\net1\\group\\g4";
	string strnet1ip					= "net\\net1\\ip";
	string strnet1ipip1					= "net\\net1\\ip\\ip1";
	string strnet1ipip2					= "net\\net1\\ip\\ip2";
	string strnet1ipip3					= "net\\net1\\ip\\ip3";
	string strnet1ipip4					= "net\\net1\\ip\\ip4";
	string strnet1subnet				= "net\\net1\\subnet";
	string strnet1subnetsn1				= "net\\net1\\subnet\\sn1";
	string strnet1subnetsn2				= "net\\net1\\subnet\\sn2";
	string strnet1subnetsn3				= "net\\net1\\subnet\\sn3";
	string strnet1subnetsn4				= "net\\net1\\subnet\\sn4";
	string strnet1ts					= "net\\net1\\ts";
	string strnet1tssn1					= "net\\net1\\ts\\sn1";
	string strnet1tssn2					= "net\\net1\\ts\\sn2";
	string strnet1tssn3					= "net\\net1\\ts\\sn3";
	string strnet1tssn4					= "net\\net1\\ts\\sn4";
	string strnet2						= "net\\net2";
	string strnet2group					= "net\\net2\\group";
	string strnet2groupg1				= "net\\net2\\group\\g1";
	string strnet2ip					= "net\\net2\\ip";
	string strnet2subnet				= "net\\net2\\subnet";
	string strnet2ts					= "net\\net2\\ts";


	



	loc.Treedb_ReopenSubKeyEx(strnet);

	loc.Treedb_ReopenSubKeyEx(strnet2);
	loc.Treedb_ReopenSubKeyEx(strnet1group);
	loc.Treedb_ReopenSubKeyEx(strnet1groupg1);
	{chen::VariableData vd("net\\net1\\group");	 loc.Treedb_InsertProperty("path", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1groupg2);
	{chen::VariableData vd("net\\net1\\group\\g1");	 loc.Treedb_InsertProperty("path", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1groupg3);
	{chen::VariableData vd("net\\net1\\group\\g1");	 loc.Treedb_InsertProperty("path", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1groupg4);
	{chen::VariableData vd("net\\net1\\group\\g1\\g2");	 loc.Treedb_InsertProperty("path", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1ip);
	loc.Treedb_ReopenSubKeyEx(strnet1ipip1);
	{chen::VariableData vd("111.111.111.111");	 loc.Treedb_InsertProperty("ip", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1ipip2);
	{chen::VariableData vd("222.222.222.222");	 loc.Treedb_InsertProperty("ip", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1ipip3);
	{chen::VariableData vd("333.333.333.333");	 loc.Treedb_InsertProperty("ip", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1ipip4);
	{chen::VariableData vd("444.444.444.444");	 loc.Treedb_InsertProperty("ip", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1subnet);
	loc.Treedb_ReopenSubKeyEx(strnet1subnetsn1);
	{chen::VariableData vd("123");	 loc.Treedb_InsertProperty("path", vd); }
	{chen::VariableData vd("");	 loc.Treedb_InsertProperty("ip", vd); }
	{chen::VariableData vd("");	 loc.Treedb_InsertProperty("ip2", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1subnetsn2);
	{chen::VariableData vd("123");	 loc.Treedb_InsertProperty("path", vd); }
	{chen::VariableData vd("");	 loc.Treedb_InsertProperty("ip", vd); }
	{chen::VariableData vd("");	 loc.Treedb_InsertProperty("ip3", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1subnetsn3);
	{chen::VariableData vd("123");	 loc.Treedb_InsertProperty("path", vd); }
	{chen::VariableData vd("");	 loc.Treedb_InsertProperty("ip", vd); }
	{chen::VariableData vd("");	 loc.Treedb_InsertProperty("ip4", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1subnetsn4);
	{chen::VariableData vd("123");	 loc.Treedb_InsertProperty("path", vd); }
	{chen::VariableData vd("");	 loc.Treedb_InsertProperty("ip", vd); }
	{chen::VariableData vd("");	 loc.Treedb_InsertProperty("ip2", vd); }
	{chen::VariableData vd("");	 loc.Treedb_InsertProperty("ip3", vd); }
	{chen::VariableData vd("");	 loc.Treedb_InsertProperty("ip4", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1ts);
	loc.Treedb_ReopenSubKeyEx(strnet1tssn1);
	{chen::VariableData vd("111");	 loc.Treedb_InsertProperty("name", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet1tssn2);
	loc.Treedb_ReopenSubKeyEx(strnet1tssn3);
	loc.Treedb_ReopenSubKeyEx(strnet1tssn4);
	loc.Treedb_ReopenSubKeyEx(strnet2);
	loc.Treedb_ReopenSubKeyEx(strnet2group);
	loc.Treedb_ReopenSubKeyEx(strnet2groupg1);
	{chen::VariableData vd("net\\net2\\group");	 loc.Treedb_InsertProperty("path", vd); }
	loc.Treedb_ReopenSubKeyEx(strnet2ip);
	loc.Treedb_ReopenSubKeyEx(strnet2subnet);
	loc.Treedb_ReopenSubKeyEx(strnet2ts);

	return true;
}


bool synDb::modifyip(string net, string ip, string key, string value)
{
	CMxHandleLoc loc;
	int nRet = loc.Treedb_Alloc("127.0.0.1", "ccubase", "testipctrl", "", ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_CreateMainKey Error!" << " strServer:" << endl;
		return false;
	};

	string strnet = "net";
	//loc.treedb_re
}