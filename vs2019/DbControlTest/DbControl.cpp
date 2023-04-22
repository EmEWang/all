
#include "DbControl.h"

void getFromTreeDb(const string& strServer, const string& strDb, const string& strPath, const string& strSubPath)
{
	CMxHandleLoc hLoc;
	int nRet = hLoc.Treedb_Alloc(strServer, strDb, strPath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << endl;
		return;
	}

	nRet = hLoc.Treedb_ReopenSubKey(strSubPath, ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error!" << endl;
		return;
	}

	string name = hLoc.Treedb_GetPropertyString("name", "");
	double price = hLoc.Treedb_GetPropertyDouble("price", 0.0);
	int value = hLoc.Treedb_GetPropertyInt("value", 0);
	char type = (char)hLoc.Treedb_GetPropertyInt("type", 0);

	cout << "name:" << name << " price:" << price << " value:" << value << " type:" << type  <<endl;

}


void setToTreeDb(const string& strServer, const string& strDb, const string& strPath, const string& strSubPath)
{
	CMxHandleLoc hLoc;
	int nRet = hLoc.Treedb_Alloc(strServer, strDb, strPath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << " strServer:" << strServer << " DB:" << strDb << endl;
		return;
	}


	CMxHandleLoc hLoc2 = hLoc;
	CMxHandleLoc hLoc3 = hLoc;

	nRet = hLoc2.Treedb_ReopenSubKey("subtest2", ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error:" << "subtest2" << endl;
		return;
	}
	//修改路径名字
	hLoc2.Treedb_RenameThisKey("subtest2_xx");

	nRet = hLoc3.Treedb_ReopenSubKey(strSubPath, ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error:" << strSubPath << endl;
		return;
	}
	//更改属性的名字 值
	hLoc3.Treedb_RenameProperty("name", "name_xx");
	hLoc3.Treedb_WriteKeyString("name_xx", "name_vvvvvv");
	string name = hLoc3.Treedb_GetPropertyString("name_xx", "");
	double price = hLoc3.Treedb_GetPropertyDouble("price", 0.0);
	int value = hLoc3.Treedb_GetPropertyInt("value", 0);
	char type = (char)hLoc3.Treedb_GetPropertyInt("type", 0);

	cout << "name:" << name << " price:" << price << " value:" << value << " type:" << type << endl;


	cout << "-----------------" << endl;

}


void init(const string& strServer, const string& strFile, const string& strMainKey, const string& strSubKey)
{
	CMxHandleLoc hLoc;
	string path;

	//file
	int nRet = hLoc.Treedb_CreateFile(strServer, strFile);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_CreateFile Error!" << " strServer:" << strServer << endl;
		return;
	}

	//maimkey
	nRet = CMxHandleLoc::Treedb_CreateMainKey(strServer, strFile, strMainKey);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_CreateMainKey Error!" << " strServer:" << strServer << endl;
		return;
	}

	//附着
	nRet = hLoc.Treedb_Alloc(strServer, strFile, strMainKey);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_CreateMainKey Error!" << " strServer:" << strServer << endl;
		return;
	}
	
	// 插入子健
	string strSub = strSubKey;
	string strSub2 = strSubKey + "2";
	nRet = hLoc.Treedb_InsertSubKey(strSub);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_InsertSubKey Error!" << " strSubKey:" << strSub << endl;
		return;
	}
	nRet = hLoc.Treedb_InsertSubKey(strSub2);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_InsertSubKey Error!" << " strSubKey:" << strSub << endl;
		return;
	}

	//插入属性
	string strSub11 = strSubKey;
	nRet = hLoc.Treedb_ReopenSubKey(strSub, ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error!" << endl;
		return;
	}

	strSub11 += "ss";
	nRet = hLoc.Treedb_InsertSubKey(strSub11);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_InsertSubKey Error!" << " strSubKey:" << strSub << endl;
		return;
	}


	strSub11 += "ss";
	nRet = hLoc.Treedb_InsertSubKey(strSub11);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_InsertSubKey Error!" << " strSubKey:" << strSub << endl;
		return;
	}


	//
	hLoc.Treedb_ReopenSubKey(strSub + "\\" + strSub11, ExistNodePath);
	//插入属性
	chen::VariableData vd11("name_str11");
	hLoc.Treedb_InsertProperty("name11", vd11);
	chen::VariableData vd12(22);
	hLoc.Treedb_InsertProperty("age11", vd12);

	//
	hLoc.Treedb_ReopenSubKey(strSub, ExistNodePath);
	//插入属性
	chen::VariableData vd("name_str");
	hLoc.Treedb_InsertProperty("name", vd);	
	chen::VariableData vd2(12);
	hLoc.Treedb_InsertProperty("age", vd2);
	chen::VariableData vd3(12.34);
	hLoc.Treedb_InsertProperty("money", vd3);
	chen::VariableData vd4('A');
	hLoc.Treedb_InsertProperty("type", vd4);
}

void readkey(CMxHandleLoc &hLoc, int length, string path, const string& strServer, const string& strFile)
{
	string strtab;
	for (int i = 0; i < length; i++)
	{
		strtab += "	";
	}
	list<string> subkeys;
	int nRet = hLoc.Treedb_GetAllSubKeys(subkeys);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_GetAllSubKeys Error!" << " strServer:" << endl;
		return;
	}
	
	for (list<string>::iterator it = subkeys.begin(); it != subkeys.end(); ++it)
	{
		string str = *it;
		//list<string>::iterator itt = it;
		cout << strtab << "subkey:	" << str << endl;

		string strpath;
		if (path.length() == 0)
		{
			strpath = str;
		}
		else
		{
			strpath = path + "\\" + str;
		}
		
		int nRet = hLoc.Treedb_ReopenSubKey(strpath);
		//int nRet = hLoc.Treedb_Alloc(strServer, strFile, str);
		if (nRet != BS_NOERROR)
		{
			cout << "Treedb_ReopenSubKey Error!" << " strServer:" << endl;
			return;
		}
		readkey(hLoc, length+1, strpath , strServer, strFile);
	}
	list<string> propety;
	nRet = hLoc.Treedb_ReopenSubKey(path);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error!" << " strServer:" << endl;
		return;
	}
	nRet = hLoc.Treedb_GetAllPropertyNames(propety);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_GetAllPropertyNames Error!" << " strServer:"  << endl;
		return;
	}
	for (list<string>::iterator it = propety.begin(); it != propety.end(); ++it)
	{
		cout << strtab << "propety:	" << *it << endl;
	}
}

void readinit(const string& strServer, const string& strFile, const string& strMainKey, const string& strSubKey)
{
	//CMxHandleLoc hLoc;
	list<string> mainkeys;
	int nRet = CMxHandleLoc::Treedb_GetAllMainKeyNames(mainkeys, strServer, strFile);

	cout << "mainkeys:>>>>" << endl;
	for (list<string>::iterator it = mainkeys.begin(); it != mainkeys.end(); ++it)
	{
		CMxHandleLoc hLoc;
		cout << *it << " ";
		nRet = hLoc.Treedb_Alloc(strServer, strFile, *it, "", ExistNodePath);
		if (nRet != BS_NOERROR)
		{
			cout << "Treedb_Alloc Error!" << " strServer:" << strServer << endl;
			return;
		}

		readkey(hLoc, 0, "", strServer, strFile);
	}
	cout << endl << "<<<<mainkeys" << endl;
	
}

void clear(const string& strServer, const string& strFile, const string& strMainKey, const string& strSubPath)
{
	CMxHandleLoc hLoc;

	//附着
	int nRet = hLoc.Treedb_Alloc(strServer, strFile, strMainKey);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_CreateMainKey Error!" << " strServer:" << strServer << endl;
		return;
	};


	//删除属性
	nRet = hLoc.Treedb_DeleteProperty("name");
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_DeleteProperty Error!" << " strServer:" << strServer << endl;
		//return;
	}
	hLoc.Treedb_ReopenSubKey("subkey");
	nRet = hLoc.Treedb_DeleteProperty("name");
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_DeleteProperty Error!" << " strServer:" << strServer << endl;
		//return;
	}
	else
	{
		cout << "Treedb_DeleteProperty Success!" << " strServer:" << strServer << endl;;
	}
	nRet = hLoc.Treedb_DeleteAllProperty();
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_DeleteAllProperty Error!" << " strServer:" << strServer << endl;
		//return;
	}
	else
	{
		cout << "Treedb_DeleteAllProperty Success!" << " strServer:" << strServer << endl;;
	}

	//Treedb_RenameSubKey
	nRet = hLoc.Treedb_RenameThisKey("ssssss");
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_RenameThisKey Error!" << " strServer:" << strServer << endl;
		//return;
	}
	else
	{
		cout << "Treedb_RenameThisKey Success!" << " strServer:" << strServer << endl;;
	}
	//Treedb_RenameSubKey 不能带目录 当前路径
	nRet = hLoc.Treedb_RenameSubKey("ssssss", "zzzzzz");   
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_RenameSubKey Error!" << " strServer:" << strServer << endl;
		//return;
	}
	else
	{
		cout << "Treedb_RenameSubKey Success!" << " strServer:" << strServer << endl;;
	}

}



void testPath()
{
	CMxHandleLoc hLoc;
	list<string> mainkeys;
	int nRet = hLoc.Treedb_Alloc("127.0.0.1", "ccubase", "Config", "",  ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << " strServer:" << endl;
		return;
	}

	//
	string strpath = "ConcurrentControl";
	nRet = hLoc.Treedb_ReopenSubKey(strpath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error!" << " strpath:" << strpath << endl;
		//return;
	}

	strpath = "Config\\ConcurrentControl";
	nRet = hLoc.Treedb_ReopenSubKey(strpath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error!" << " strpath:" << strpath << endl;
		//return;
	}

	strpath = "ConcurrentControl\\Libvirt";
	nRet = hLoc.Treedb_ReopenSubKey(strpath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error!" << " strpath:" << strpath << endl;
		//return;
	}
	strpath = "Libvirt";
	nRet = hLoc.Treedb_ReopenSubKey(strpath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error!" << " strpath:" << strpath << endl;
		//return;
	}

	strpath = "Config\\ConcurrentControl\\Libvirt";
	nRet = hLoc.Treedb_ReopenSubKey(strpath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error!" << " strpath:" << strpath << endl;
		//return;
	}

	strpath = "ccubase\\ConcurrentControl\\Libvirt";
	nRet = hLoc.Treedb_ReopenSubKey(strpath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error!" << " strpath:" << strpath << endl;
		//return;
	}
}


void readint()
{
	CMxHandleLoc hLoc;
	int nRet = hLoc.Treedb_Alloc("127.0.0.1", "ipctrl", "Co", "", ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << " strServer:" << endl;
		return;
	}
	
	hLoc.Treedb_ReopenSubKey("Co_1\\Net\\Net.1\\SubNet\\192.168.2.0/24");

	std::cout << "	int:" << hLoc.Treedb_GetPropertyInt("lIp", 0) << endl;
	std::cout << "	int64:" << hLoc.Treedb_GetPropertyInt64("lIp", 0) << endl;

	
}


void editint() 
{
	CMxHandleLoc hLoc;
	int nRet = hLoc.Treedb_Alloc("127.0.0.1", "ipctrl", "Co", "", ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << " strServer:" << endl;
		return;
	}


	unsigned int iIp = 3232236075;
	unsigned int iMask = 4294967040;

	nRet = hLoc.Treedb_ReopenSubKey("Co_12\\Net\\Net3\\SunNet\\192.168.2.0/24");


	nRet = hLoc.Treedb_WriteKeyInt64("lIp", iIp);
	nRet = hLoc.Treedb_WriteKeyInt64("lMask", iMask);

	int nManage = hLoc.Treedb_GetPropertyInt64("lIp", 1);
	int nManage2 = hLoc.Treedb_GetPropertyInt64("lMask", 1);

	unsigned int iIp2 = nManage;
	unsigned int iMask2 = nManage2;

	int iCount = (~iMask2 | iIp2) - (iMask2 & iIp2);

	std::cout << "ipcont:" << iCount << endl;

	std::cout << "	int:" << hLoc.Treedb_GetPropertyInt("lIp", 0) << endl;
	std::cout << "	int64:" << hLoc.Treedb_GetPropertyInt64("lIp", 0) << endl;


}


void sendMq(const string& server, const string& name)
{
	CMxHandleLoc hLoc;
	list<string> mainkeys;
	int nRet = hLoc.MQdb_Alloc(server, name, "", CMxVar::MUSTEXISTQ);
	if (nRet != BS_NOERROR)
	{
		cout << "MQdb_Alloc Error!" << " strServer:" << endl;
		return;
	}

	hLoc.MQdb_ClearMQ();
	chen::VariableData rv;
	string args = "123456";
	rv.PutBinData(args.c_str(), args.size());	
	std::string szLabel = "111_111";
	std::string szLabel2 = "111_222";
	ui64 uid;

	nRet = hLoc.MQdb_PushMessage(rv, szLabel, uid);
	nRet = hLoc.MQdb_PushMessage(rv, szLabel, uid);


	string args2 = "123456789";
	//rv.Clear();
	rv.PutBinData(args2.c_str(), args2.size());
	nRet = hLoc.MQdb_PushMessage(rv, szLabel2, uid);
	nRet = hLoc.MQdb_PushMessage(rv, szLabel2, uid);
	//
	if (nRet != BS_NOERROR)
	{
		cout << "label:" << szLabel << " uid:" << uid << " args:" << args << endl;
	}

	time_t tmCreateTime = 0;
	chen::VariableData rv2;	
	ui64 uid2 = 0;
	int nWaitTime = 30000;
	rv2.Clear();
	nRet = hLoc.MQdb_PopMessage(rv2, szLabel, tmCreateTime, uid2, nWaitTime);
	if (nRet == BS_NOERROR)
	{
		char *m_data = new char[rv2.m_bin.len + 2];
		memset(m_data, 0, rv2.m_bin.len + 2);
		int nlen = rv2.m_bin.len;
		rv2.GetBinData(m_data, nlen);
		cout << "label:" << szLabel << " uid:" << uid2 << " tm:" << tmCreateTime << " len:" << nlen << " buff:"  << m_data << endl;
	}

	tmCreateTime = 0;
	uid2 = 0;
	nWaitTime = 30000;
	rv2.Clear();
	nRet = hLoc.MQdb_PopMessage(rv2, szLabel, tmCreateTime, uid2, nWaitTime);
	if (nRet == BS_NOERROR)
	{
		char* m_data = new char[rv2.m_bin.len + 2];
		memset(m_data, 0, rv2.m_bin.len + 2);
		int nlen = rv2.m_bin.len;
		rv2.GetBinData(m_data, nlen);
		cout << "label:" << szLabel << " uid:" << uid2 << " tm:" << tmCreateTime << " len:" << nlen << " buff:" << m_data << endl;
	}

	tmCreateTime = 0;
	uid2 = 0;
	nWaitTime = 30000;
	rv2.Clear();
	nRet = hLoc.MQdb_PopMessage(rv2, szLabel, tmCreateTime, uid2, nWaitTime);
	if (nRet == BS_NOERROR)
	{
		char* m_data = new char[rv2.m_bin.len + 2];
		memset(m_data, 0, rv2.m_bin.len + 2);
		int nlen = rv2.m_bin.len;
		rv2.GetBinData(m_data, nlen);
		cout << "label:" << szLabel << " uid:" << uid2 << " tm:" << tmCreateTime << " len:" << nlen << " buff:" << m_data << endl;
	}

	tmCreateTime = 0;
	uid2 = 0;
	nWaitTime = 30000;
	rv2.Clear();
	nRet = hLoc.MQdb_PopMessage(rv2, szLabel2, tmCreateTime, uid2, nWaitTime);
	if (nRet == BS_NOERROR)
	{
		char* m_data = new char[rv2.m_bin.len + 2];
		memset(m_data, 0, rv2.m_bin.len + 2);
		int nlen = rv2.m_bin.len;
		rv2.GetBinData(m_data, nlen);
		cout << "label:" << szLabel << " uid:" << uid2 << " tm:" << tmCreateTime << " len:" << nlen << " buff:" << m_data << endl;
	}

	tmCreateTime = 0;
	uid2 = 0;
	nWaitTime = 30000;
	rv2.Clear();
	nRet = hLoc.MQdb_PopMessage(rv2, szLabel2, tmCreateTime, uid2, nWaitTime);
	if (nRet == BS_NOERROR)
	{
		char* m_data = new char[rv2.m_bin.len + 2];
		memset(m_data, 0, rv2.m_bin.len + 2);
		int nlen = rv2.m_bin.len;
		rv2.GetBinData(m_data, nlen);
		cout << "label:" << szLabel << " uid:" << uid2 << " tm:" << tmCreateTime << " len:" << nlen << " buff:" << m_data << endl;
	}

	tmCreateTime = 0;
	uid2 = 0;
	nWaitTime = 30000;
	rv2.Clear();
	nRet = hLoc.MQdb_PopMessage(rv2, szLabel2, tmCreateTime, uid2, nWaitTime);
	if (nRet == BS_NOERROR)
	{
		char* m_data = new char[rv2.m_bin.len + 2];
		memset(m_data, 0, rv2.m_bin.len + 2);
		int nlen = rv2.m_bin.len;
		rv2.GetBinData(m_data, nlen);
		cout << "label:" << szLabel << " uid:" << uid2 << " tm:" << tmCreateTime << " len:" << nlen << " buff:" << m_data << endl;
	}

	hLoc.MQdb_ClearMQ();

	hLoc.MQdb_DeleteMQ();

}

void sendMq2(const string& server, const string& name)
{
	CMxHandleLoc hLoc;
	int nRet = hLoc.MQdb_Alloc(server, name, "", CMxVar::MUSTEXISTQ);
	if (nRet != BS_NOERROR)
	{
		cout << "DB Error" << __FUNCTION__ << endl;
		return;
	}

	//nRet = hLoc.MQdb_ClearMQ();

	string str = "1234567890abc";
	int ii = 345;
	chen::VariableData vd;
	float ff = 1.2345f;
	int len = 0;
	//vd.SerialData((char*)&ii, &len);
	char ccc[111] = "1234567890abc";
	vd.UnSerial(ccc, strlen(ccc));

	//vd.SerialData(ccc, &len);
	//vd.PutBinData((char*)(&ff), sizeof(ff));

	

	ui64 index;
	string label = "1_test";
	nRet = hLoc.MQdb_PushMessage(vd, label, index);
	if (nRet != BS_NOERROR)
	{
		cout << "DB Error:" << __FUNCTION__ <<endl;
		return;
	}

	cout << "put:[str]" << str << " [ff]" << ff << " [label]" << label << endl;
	//nRet = hLoc.MQdb_DeleteMQ();
}


void getMq2(const string& server, const string& name)
{
	CMxHandleLoc hLoc;
	int nRet = hLoc.MQdb_Alloc(server, name, "", CMxVar::MUSTEXISTQ);
	if (nRet != BS_NOERROR)
	{
		cout << "DB Error" << __FUNCTION__ << endl;
		return;
	}

	//nRet = hLoc.MQdb_ClearMQ();

	string str ;
	chen::VariableData vd;
	float ff = 1.1f;
	ui64 index = 0;
	time_t tm = 0;
	string label;
	int nWaitTime = 30000;

	nRet = hLoc.MQdb_PopMessage(vd, label, tm, index, nWaitTime);
	if (nRet != BS_NOERROR)
	{
		cout << "DB Error:" << __FUNCTION__ << endl;
		return;
	}

	char* cc = vd;
	//str = cc;
	int ii = 0;
	int len = sizeof(ff);

	char chch[111] = { 0 };
	//vd.UnSerial((char*)(&ii), 4);
	vd.SerialData(chch, &ii);
	//vd.GetBinData((char*)(&ff), len);


	cout << "put:[str]" << str << " [ff]" << ff << " [label]" << label << endl;



	//nRet = hLoc.MQdb_DeleteMQ();
}


void sendMq3(const string& server, const string& name, const string& label, const string & file)
{
	CMxHandleLoc hLoc;
	int nRet = hLoc.MQdb_Alloc(server, name, "", CMxVar::MUSTEXISTQ);
	if (nRet != BS_NOERROR)
	{
		cout << "MQdb_Alloc Error" << __FUNCTION__ << endl;
		return;
	}


	fstream file1;
	//file1.open(file, ios::binary | ios::in, 0);
	file1.open(file);
	if (!file1.is_open())
	{
		cout << "open Error " << file << endl;
		return;
	}
	file1.seekg(0, ios::end);
	int len = file1.tellg(); // 文件大小
	char* s = new char[len];
	file1.seekg(0, ios::beg);
	file1.read(s, len);
	file1.close();


	chen::VariableData vd;
	if (!vd.PutBinData(s, len))
	{
		delete[] s;
		cout << "PutBinData Error " << file << endl;
		return;
	}
	delete[] s;

	ui64 uid = 0;
	nRet = hLoc.MQdb_PushMessage(vd, label, uid);
	if (nRet != BS_NOERROR)
	{
		cout << "MQdb_PushMessage Error:" << __FUNCTION__ << endl;
		return;
	}

	cout << "[sendMq3]finish" << "[label]" << label << "[len]" << len << endl;
}


void testInsertExistSubkey(const string& strServer, const string& strDb, const string& strPath)
{
	CMxHandleLoc hLoc;
	int nRet = hLoc.Treedb_Alloc(strServer, strDb, strPath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << endl;
		return;
	}

	string co = "zzz";
	nRet = hLoc.Treedb_InsertSubKey(co);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_InsertSubKey Error!" << endl;
		return;
	}

	//string name = hLoc.Treedb_GetPropertyString("name", "");
	//double price = hLoc.Treedb_GetPropertyDouble("price", 0.0);
	//int value = hLoc.Treedb_GetPropertyInt("value", 0);
	//char type = (char)hLoc.Treedb_GetPropertyInt("type", 0);

	//cout << "name:" << name << " price:" << price << " value:" << value << " type:" << type << endl;
}


void testInterface(const string& strServer, const string& strPath)
{
	CMxHandleLoc hdloc;
	int nRet = 0;
	nRet = hdloc.Treedb_Alloc(strServer, IPCTRL, COMPANYEKEY, "");

	if (nRet != BS_NOERROR)
		return;
	//nRet = CMxVar::ReopenNewKey(hdloc.GetConfHandle()->m_hd, strPath, "", ExistNodePath);
	nRet = CMxVar::ReopenSubKey(hdloc.GetConfHandle()->m_hd, strPath);
	if (nRet != BS_NOERROR)
		return;
}

void testBableDB(const string& server, const string& table, const string& tablename)
{
	CMxHandleLoc hdloc;
	int nRet = 0;
	nRet = hdloc.Tabledb_Alloc(server, table, "", "");
	if (nRet != BS_NOERROR)
	{
		printf("Tabledb_Alloc error [ret]%d[server]%s[table]%s\n", nRet, server.c_str(), table.c_str());
		return;
	}
	BSFIELDINFOLIST bfil;


	bs_tdfield bsf;

	strcpy_s(bsf.name, 30, "tt_str");
	bsf.uDataLen = 0;
	bsf.uType = VDT_STR;
	bsf.uFlag = 0;
	bfil.push_back(&bsf);

	bs_tdfield bsf2;
	strcpy_s(bsf2.name, 30, "tt_int32");
	bsf2.uDataLen = 0;
	bsf2.uType = VDT_I32;
	bsf2.uFlag = 0;
	bfil.push_back(&bsf2);

	nRet = hdloc.Tabledb_CreateTable(tablename, bfil);
	if (nRet != BS_NOERROR)
	{
		printf("Tabledb_CreateTable error [ret]%d[server]%s[table]%s[tablename]\n", nRet, server.c_str(), table.c_str(), tablename.c_str());
		return;
	};
}

void testKeyExist(const string& server, const string& db, const string& mainkay, const string& subkey)
{
	CMxHandleLoc hdloc;
	int nRet = 0;
	nRet = hdloc.Treedb_Alloc(server, db, mainkay, "", ExistDotPath);

	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << endl;
		return;
	}

	nRet = CMxVar::ReopenSubKey(hdloc.GetConfHandle()->m_hd, subkey, ExistDotPath);
	if (nRet == BS_NOERROR)
		cout << subkey << " exist" << endl;
	else
		cout << subkey << " not exist" << endl;
}

void testKeyPropertyExist(const string& server, const string& db, const string& mainkey, const string& subkey, const string& property)
{
	CMxHandleLoc hdloc;
	int nRet = 0;
	nRet = hdloc.Treedb_Alloc(server, db, mainkey, "", ExistDotPath);

	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << endl;
		return;
	}

	nRet = CMxVar::ReopenSubKey(hdloc.GetConfHandle()->m_hd, subkey, ExistNodePath);
	if (nRet == BS_NOERROR)
		cout << subkey << " exist" << endl;
	else
	{
		cout << subkey << " not exist" << endl;
		return;
	}

	string str1 = hdloc.Treedb_GetPropertyString(property, "xxx");               // 存在属性则返回属性 不存在则返回你默认值xxx

	printf("property %s  str2 %s\n", property.c_str(), str1.c_str());
}

void testTableDB(const string& server, const string& DB, const string& table, const string& field)
{
	BSHANDLE hd = BS_INVALID_HANDLE;
	CMxHandleLoc hdloc;
	int nRet = hdloc.Tabledb_Alloc(server, DB, "", "");
	if (nRet != BS_NOERROR)
	{
		cout << "Tabledb_Alloc Error!" << endl;
		return;
	}

	string logname = "testDBXXX.log";
	char buff[1024];
	sprintf(buff, "123456\n");
	fstream fstr;
	fstr.open(logname, std::fstream::in | std::fstream::out | std::fstream::app);
	fstr.write(buff, strlen(buff));
	fstr.close();

	hd = hdloc.GetConfHandle()->m_hd;
	BSHANDLE hRes = BS_INVALID_HANDLE;
	unsigned int uulim = 12040000;
	unsigned long long int ll = 1651135828;
	chen::VariableData vFValue_ = ll;
	unsigned long long int ll2 = 1651135830;
	chen::VariableData EndValue_ = ll2;
	chen::VariableData * pEndValue_ = &EndValue_;
	list<string> lsttables;
	nRet = ::bs_tabledb_get_all_tablenames(hd, lsttables);
	BSFIELDINFOLIST lFieldList;
	nRet = ::bs_tabledb_get_fields(hd, table.c_str(), lFieldList);
	nRet = ::bs_tabledb_get_record_by_field(hd, table.c_str(),
		field.c_str(), vFValue_,pEndValue_, 0, 0, uulim, hRes);
	if (nRet != BS_NOERROR)
	{
		cout << "bs_tabledb_get_record_by_field Error!" << endl;
		return;
	}

	BSHANDLE hCR = BS_INVALID_HANDLE;

	CMxHandleLoc m_hd;
	m_hd.Tabledb_GetCursor(hRes, hCR);
	FIELDVALUEMAP vm;
	time_t ctm;
	chen::VariableData rv;
	std::string strKeyName;
	while (BS_NOERROR == m_hd.Tabledb_CursorNext(hCR, vm, ctm))
	{
		for (auto it = vm.begin(); it != vm.end(); it++)
		{
			strKeyName = it->first;			
			rv = it->second;
		}		
	}

	bs_close_handle(hCR);
}

void testTableDBInsert(const string& server, const string& DB, const string& table)
{
	CMxHandleLoc m_hd;
	int nRet = m_hd.Tabledb_Alloc(server, DB, "", "");
	if (nRet != BS_NOERROR)
	{
		cout << "Tabledb_Alloc Error!" << endl;
		return;
	}
	//nRet = m_hd.Tabledb_ReopenDb(table, "", "");
	BSFIELDVALUELIST fieldList;
	chen::VariableData rv;
	rv = "10.10.10.10";              //Srcaddr
	fieldList.push_back(rv);
	rv = "11.11.11.11";              //Dstaddr
	fieldList.push_back(rv);
	rv = (unsigned short)111;                        //Port
	fieldList.push_back(rv);
	rv = (unsigned short)222;                        //Protocol
	fieldList.push_back(rv);
	rv = 333;                        //bytes
	fieldList.push_back(rv);
	rv = 444;                        //packets
	fieldList.push_back(rv);
	rv = (unsigned int)1652946601;                 //start_time
	fieldList.push_back(rv);

	nRet = m_hd.Tabledb_InsertRecord(table, fieldList);
	if (nRet == BS_TBDB_NOFINDTABLE)
	{
		BSFIELDINFOLIST flist;
		bs_tdfield* pFiled;

		pFiled = new bs_tdfield;
		//if (!pFiled)
		//	return BS_ERROR_ALLOCMEMORY;
		sprintf_s(pFiled->name, sizeof(pFiled->name), "Srcaddr");
		pFiled->uType = VDT_STR;
		pFiled->uFlag = 0;
		pFiled->uDataLen = 100;	
		flist.push_back(pFiled);

		pFiled = new bs_tdfield;
		//if (!pFiled)
		//	return BS_ERROR_ALLOCMEMORY;
		sprintf_s(pFiled->name, sizeof(pFiled->name), "Dstaddr");
		pFiled->uType = VDT_STR;
		pFiled->uFlag = 0;
		pFiled->uDataLen = 100;
		flist.push_back(pFiled);

		pFiled = new bs_tdfield;
		//if (!pFiled)
		//	return BS_ERROR_ALLOCMEMORY;
		sprintf_s(pFiled->name, sizeof(pFiled->name), "Port");
		pFiled->uType = VDT_UI16;
		pFiled->uFlag = 0;
		pFiled->uDataLen = 100;
		flist.push_back(pFiled);

		pFiled = new bs_tdfield;
		//if (!pFiled)
		//	return BS_ERROR_ALLOCMEMORY;
		sprintf_s(pFiled->name, sizeof(pFiled->name), "Protocol");
		pFiled->uType = VDT_UI16;
		pFiled->uFlag = 0;
		pFiled->uDataLen = 100;
		flist.push_back(pFiled);

		pFiled = new bs_tdfield;
		//if (!pFiled)
		//	return BS_ERROR_ALLOCMEMORY;
		sprintf_s(pFiled->name, sizeof(pFiled->name), "bytes");
		pFiled->uType = VDT_UI32;
		pFiled->uFlag = 0;
		pFiled->uDataLen = 100;
		flist.push_back(pFiled);

		pFiled = new bs_tdfield;
		//if (!pFiled)
		//	return BS_ERROR_ALLOCMEMORY;
		sprintf_s(pFiled->name, sizeof(pFiled->name), "packets");
		pFiled->uType = VDT_UI32;
		pFiled->uFlag = 0;
		pFiled->uDataLen = 100;
		flist.push_back(pFiled);

		pFiled = new bs_tdfield;
		//if (!pFiled)
		//	return BS_ERROR_ALLOCMEMORY;
		sprintf_s(pFiled->name, sizeof(pFiled->name), "start_time");
		pFiled->uType = VDT_UI32;
		pFiled->uFlag = 0;
		pFiled->uDataLen = 100;
		flist.push_back(pFiled);

		nRet = m_hd.Tabledb_CreateTable(table, flist);
		if (nRet != BS_NOERROR)
		{
			cout << "Tabledb_CreateTable Error!" << endl;
			return;
		}

		nRet = m_hd.Tabledb_InsertRecord(table, fieldList);
	}


	if (nRet != BS_NOERROR)
	{
		cout << "Tabledb_InsertRecord Error!" << endl;
		return;
	}
}


void ClearIP(const string& server, const string& co, const string& net)
{
	//CMxHandleLoc hLoc;
	//int sleeptime = 1000;
	//int commitennum = 60000;


	//// 1
	//int nRet = hLoc.Treedb_Alloc(server, "ipctrl", "Co");
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_Alloc Error" << "[server]" << server << endl;
	//	return;
	//}
	//cout << "1 Treedb_Alloc success" << endl;
	//Sleep(sleeptime);


	//// 2
	//char tmp[100] = { 0 };
	//sprintf(tmp, "%s\\Net\\%s", co.c_str(), net.c_str());
	//string strMain = tmp;
	//string strMainNet = strMain + "\\SubNet";
	//string strMainIP = strMain + "\\IP";

	//nRet = hLoc.Treedb_ReopenSubKey(strMainNet);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_ReopenSubKey Error" << "[strMainNet]" << strMainNet << endl;
	//	return;
	//}

	////map<string, pair<unsigned int, unsigned int> > netrange;
	//list<pair<unsigned int, unsigned int> > netrangelst;
	//list<string> netlist;

	//nRet = hLoc.Treedb_GetAllSubKeys(netlist);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_GetAllSubKeys [net] Error" << endl;
	//	return;
	//}
	//printf("2 GET_ALL_Net %d\n", netlist.size());
	//Sleep(sleeptime);


	//// 3
	//CSSubNet cnet;
	//int index = 0;
	//string SubNetCur;
	//for (auto it:netlist)
	//{
	//	SubNetCur = strMainNet + "\\" + it;
	//	nRet = hLoc.Treedb_ReopenSubKey(SubNetCur);
	//	if (nRet == BS_NOERROR)
	//	{
	//		string szip = hLoc.Treedb_GetPropertyString("ip", "");
	//		string szmask = hLoc.Treedb_GetPropertyString("mask", "");

	//		if (szip.size() == 0 || szip.find('.') == string::npos)
	//		{
	//			index++;
	//			printf("[%d][SubNet]%s  szip error %s\n", index, SubNetCur.c_str(), szip.c_str());
	//			continue;
	//		}

	//		if (szmask.size() == 0 || szmask.find('.') == string::npos)
	//		{
	//			index++;
	//			printf("[%d][SubNet]%s  szmask error %s\n", index, SubNetCur.c_str(), szmask.c_str());
	//			continue;
	//		}

	//		cnet.m_szIp = szip;
	//		cnet.m_szMask = szmask;

	//		unsigned lo = 0;
	//		unsigned hi = 0;
	//		cnet.GetIpScope3(lo, hi);
	//		netrangelst.push_back(std::make_pair(lo, hi));
	//	}
	//	else
	//	{
	//		cout << "Treedb_ReopenSubKey error " << SubNetCur << "[nRet]" << nRet << endl;
	//		return;
	//	}
	//}

	//if (index !=0)
	//{
	//	cout << "[SubNet]Error %d" << index << endl;
	//	return;
	//}
	//printf("3 CAL_ALL_Net %d\n", netlist.size());
	//Sleep(sleeptime);


	//// 4
	//list<string> iplist;
	//nRet = hLoc.Treedb_ReopenSubKey(strMainIP);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_ReopenSubKey Error" << "[strMainIP]" << strMainIP  << "[nRet]" << nRet << endl;
	//	return;
	//}

	//nRet = hLoc.Treedb_GetAllSubKeys(iplist);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_GetAllSubKeys ip Error" << "[strMainIP]" << strMainIP << "[nRet]" << nRet << endl;
	//	return;
	//}
	//printf("4 GET_ALL_ip %d\n", iplist.size());
	//Sleep(sleeptime);


	//// 5
	//hLoc.Treedb_BeginTransaction();
	//index = 0;
	//int index2 = 0;
	//bool bok = true;	
	//int skip = 100;
	//string IPCur;
	//for (auto it : iplist)
	//{
	//	++index;
	//	bool bdl = true;
	//	IPCur = strMainIP + "\\" + it;
	//	nRet = hLoc.Treedb_ReopenSubKey(IPCur);
	//	if ( nRet == BS_NOERROR)
	//	{
	//		string szip = hLoc.Treedb_GetPropertyString("ip", "");

	//		if (szip.size() == 0 || szip.find('.') == string::npos)
	//		{
	//			++index2;
	//			printf("[%d][IP]%s ip error %s\n", index, IPCur.c_str(), szip.c_str());
	//			//nRet = hLoc.Treedb_DeleteSubKey(IPCur);
	//			nRet = hLoc.Treedb_DeleteThisKey();
	//			if (nRet != BS_NOERROR)
	//			{
	//				bok = false;
	//				//printf("Treedb_DeleteSubKey error %s----------------\n", it.c_str());
	//				printf("[%d][IP]%s Treedb_DeleteThisKey error %s\n", index, IPCur.c_str(), szip.c_str());
	//				break;
	//				//continue;
	//			}
	//		}

	//		unsigned int  uip  = 0;
	//		uip = CSSubNet::StrToInt(szip);

	//		for (auto it2 : netrangelst)
	//		{
	//			if (uip <= it2.second && uip >= it2.first)
	//			{
	//				bdl = false;
	//				break;					
	//			}
	//		}

	//		if (bdl)
	//		{
	//			++index2;

	//			if (index % skip == 0)
	//			{
	//				printf("[all]%d[del]%d dead ip delete %s\n", index, index2, IPCur.c_str());
	//			}				
	//			//nRet = hLoc.Treedb_DeleteSubKey(nn);
	//			nRet = hLoc.Treedb_DeleteThisKey();
	//			if (nRet != BS_NOERROR)
	//			{
	//				bok = false;
	//				printf("Treedb_DeleteSubKey error %s----------------\n", IPCur.c_str());
	//				break;
	//				//continue;
	//			}

	//			if (index2 >= commitennum)
	//			{
	//				break;
	//			}
	//		}
	//		//else
	//		//{
	//		//	printf("[%d]no delete    %s----------------\n", ++index3, nn.c_str());;
	//		//}
	//	}
	//	else
	//	{
	//		cout << "Treedb_ReopenSubKey ip error " << IPCur << "[nRet]" << nRet << endl;
	//		break;
	//		//continue;
	//	}
	//}

	//printf("[SUM][all]%d[del]%d[dead_ip_delete]%s\n", index, index2, strMainIP.c_str());

	//if (!bok)
	//{
	//	printf("clear error ----------------\n");
	//	hLoc.Treedb_RollbackTransaction();
	//	return;
	//}

	//hLoc.Treedb_CommitTransaction();
	//printf("5 clear success ----------------\n");
}

void ClearIPOnce(const string& server, const string& co, const string& net)
{
	//CMxHandleLoc hLoc;
	//int sleeptime = 1000;
	//int sleeptime2 = 1000;
	//int commitennum = 101;


	//// 1
	//int nRet = hLoc.Treedb_Alloc(server, "ipctrl", "Co");
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_Alloc Error" << "[server]" << server << endl;
	//	return;
	//}
	//cout << "1 Treedb_Alloc success" << endl;
	//Sleep(sleeptime);


	//// 2
	//char tmp[100] = { 0 };
	//sprintf(tmp, "%s\\Net\\%s", co.c_str(), net.c_str());
	//string strMain = tmp;
	//string strMainNet = strMain + "\\SubNet";
	//string strMainIP = strMain + "\\IP";

	//nRet = hLoc.Treedb_ReopenSubKey(strMainNet);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_ReopenSubKey Error" << "[strMainNet]" << strMainNet << endl;
	//	return;
	//}

	////map<string, pair<unsigned int, unsigned int> > netrange;
	//list<pair<unsigned int, unsigned int> > netrangelst;
	//list<string> netlist;

	//nRet = hLoc.Treedb_GetAllSubKeys(netlist);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_GetAllSubKeys [net] Error" << endl;
	//	return;
	//}
	//printf("2 GET_ALL_Net %d\n", netlist.size());
	//Sleep(sleeptime);


	//// 3
	//CSSubNet cnet;
	//int index = 0;
	//string SubNetCur;
	//for (auto it : netlist)
	//{
	//	SubNetCur = strMainNet + "\\" + it;
	//	nRet = hLoc.Treedb_ReopenSubKey(SubNetCur);
	//	if (nRet == BS_NOERROR)
	//	{
	//		string szip = hLoc.Treedb_GetPropertyString("ip", "");
	//		string szmask = hLoc.Treedb_GetPropertyString("mask", "");

	//		if (szip.size() == 0 || szip.find('.') == string::npos)
	//		{
	//			index++;
	//			printf("[%d][SubNet]%s  szip error %s\n", index, SubNetCur.c_str(), szip.c_str());
	//			continue;
	//		}

	//		if (szmask.size() == 0 || szmask.find('.') == string::npos)
	//		{
	//			index++;
	//			printf("[%d][SubNet]%s  szmask error %s\n", index, SubNetCur.c_str(), szmask.c_str());
	//			continue;
	//		}

	//		cnet.m_szIp = szip;
	//		cnet.m_szMask = szmask;

	//		unsigned lo = 0;
	//		unsigned hi = 0;
	//		cnet.GetIpScope3(lo, hi);
	//		netrangelst.push_back(std::make_pair(lo, hi));
	//	}
	//	else
	//	{
	//		cout << "Treedb_ReopenSubKey error " << SubNetCur << "[nRet]" << nRet << endl;
	//		return;
	//	}
	//}

	//if (index != 0)
	//{
	//	cout << "[SubNet]Error %d" << index << endl;
	//	return;
	//}
	//printf("3 CAL_ALL_Net %d\n", netlist.size());
	//Sleep(sleeptime);


	//// 4
	//list<string> iplist;
	//nRet = hLoc.Treedb_ReopenSubKey(strMainIP);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_ReopenSubKey Error" << "[strMainIP]" << strMainIP << "[nRet]" << nRet << endl;
	//	return;
	//}

	//nRet = hLoc.Treedb_GetAllSubKeys(iplist);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_GetAllSubKeys ip Error" << "[strMainIP]" << strMainIP << "[nRet]" << nRet << endl;
	//	return;
	//}
	//printf("4 GET_ALL_ip %d\n", iplist.size());
	//Sleep(sleeptime);


	//// 5	
	//index = 0;
	//int index2 = 0;
	//int index3 = 0;
	//bool bok = true;
	//int skip = 100;
	//string IPCur;

	//auto itcur = iplist.begin();
	//auto itnxt = itcur;

	//while (itcur != iplist.end())
	//{
	//	hLoc.Treedb_BeginTransaction();
	//	++index3;
	//	index2 = 0;
	//	
	//	printf("\n>>>\n");
	//	while ((itcur = itnxt) != iplist.end())
	//	{
	//		++index;
	//		++itnxt;
	//		bool bdl = true;
	//		IPCur = strMainIP + "\\" + *itcur;
	//		nRet = hLoc.Treedb_ReopenSubKey(IPCur);
	//		if (nRet == BS_NOERROR)
	//		{
	//			string szip = hLoc.Treedb_GetPropertyString("ip", "");

	//			if (szip.size() == 0 || szip.find('.') == string::npos)
	//			{
	//				++index2;
	//				printf("[all]%d[del]%d[cnt]%d[IP]%s ip error %s\n", index, index2, index3, IPCur.c_str(), szip.c_str());
	//				//nRet = hLoc.Treedb_DeleteSubKey(IPCur);
	//				nRet = hLoc.Treedb_DeleteThisKey();
	//				if (nRet != BS_NOERROR)
	//				{
	//					bok = false;
	//					//printf("Treedb_DeleteSubKey error %s----------------\n", it.c_str());
	//					printf("[all]%d[del]%d[cnt]%d[IP]%s Treedb_DeleteThisKey error %s\n", index, index2, index3, IPCur.c_str(), szip.c_str());
	//					break;
	//					//continue;
	//				}
	//			}

	//			unsigned int  uip = 0;
	//			uip = CSSubNet::StrToInt(szip);

	//			for (auto it2 : netrangelst)
	//			{
	//				if (uip <= it2.second && uip >= it2.first)
	//				{
	//					bdl = false;
	//					break;
	//				}
	//			}

	//			if (bdl)
	//			{
	//				++index2;

	//				if (index % skip == 0)
	//				{
	//					printf("[all]%d[del]%d[cnt]%d dead ip delete %s\n", index, index2, index3, IPCur.c_str());
	//				}
	//				//nRet = hLoc.Treedb_DeleteSubKey(nn);
	//				nRet = hLoc.Treedb_DeleteThisKey();
	//				if (nRet != BS_NOERROR)
	//				{
	//					bok = false;
	//					printf("[all]%d[del]%d[cnt]%d Treedb_DeleteSubKey error %s\n", index, index2, index3, IPCur.c_str());
	//					break;
	//					//continue;
	//				}

	//				if (index2 >= commitennum)
	//				{
	//					break;
	//				}
	//			}
	//			//else
	//			//{
	//			//	printf("[%d]no delete    %s----------------\n", ++index3, nn.c_str());;
	//			//}
	//		}
	//		else
	//		{
	//			//cout << "Treedb_ReopenSubKey ip error " << IPCur << "[nRet]" << nRet << endl;
	//			printf("[all]%d[del]%d[cnt]%d Treedb_ReopenSubKey error %s ret %d\n", index, index2, index3, IPCur.c_str(), nRet);
	//			break;
	//			//continue;
	//		}

	//	}

	//	if (!bok)
	//	{
	//		nRet = hLoc.Treedb_RollbackTransaction();
	//		printf("[all]%d[del]%d[cnt]%d Treedb_RollbackTransaction[nRet]%d clear error ----------------\n", index, index2, index3, nRet);
	//		printf("<<<\n");
	//		break;
	//	}

	//	nRet = hLoc.Treedb_CommitTransaction();
	//	printf("[all]%d[del]%d[cnt]%d Treedb_CommitTransaction [nRet]%d clear success ----------------\n", index, index2, index3, nRet);
	//	printf("<<<\n");

	//	Sleep(sleeptime2);
	//}	


	//printf("[SUM][all]%d[del]%d[cnt]%d[dead_ip_delete]%s\n", index, index2, index3,strMainIP.c_str());
	//Sleep(sleeptime);
	//if (!bok)
	//{
	//	printf("clear error ----------------\n");
	//	return;
	//}

	//printf("5 clear success ----------------\n");
}

void ClearIP2(const string& server, const string& co, const string& net)
{
	////CMxHandleLoc hLoc;

	//BSHANDLE hHandle = BS_INVALID_HANDLE;
	//int nRet = bs_treedb_open(hHandle, "ipctrl", "", "", TRDB_OPKF_OPENEXIST, co.c_str(), server.c_str(), 0);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "bs_treedb_open Error" << "[nRet]" << nRet << endl;
	//	return;
	//}

	//int sleeptime = 1000;

	//cout << "1 Treedb_CreateMainKey success" << endl;
	//Sleep(sleeptime);

	//char tmp[100] = { 0 };
	//sprintf(tmp, "%s\\Net\\%s", co.c_str(), net.c_str());
	//string strMain = tmp;

	//string strMainNet = strMain + "\\SubNet";
	//string strMainIP = strMain + "\\IP";


	////nRet = hLoc.Treedb_ReopenSubKey(strMainNet);
	//nRet = bs_treedb_open_subkey(hHandle, strMainNet.c_str(), TRDB_OPKF_OPENEXIST);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "bs_treedb_open_subkey Error" << "[strMainNet]" << strMainNet << "[nRet]" << nRet << endl;
	//	return;
	//}

	//map<string, pair<unsigned int, unsigned int> > netrange;
	//list<pair<unsigned int, unsigned int> > netrangelst;
	//list<string> netlist;

	////nRet = hLoc.Treedb_GetAllSubKeys(netlist);
	//nRet = bs_treedb_get_subkeys(hHandle, netlist);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "bs_treedb_get_subkeys [net] Error" << "[nRet]" << nRet << endl;
	//	return;
	//}

	//printf("2 GET_ALL_Net %d\n", netlist.size());
	//Sleep(sleeptime);

	//CSSubNet cnet;
	//int index = 0;
	//string nn;
	//for (auto it : netlist)
	//{
	//	nn = strMainNet + "\\" + it;
	//	//nRet = hLoc.Treedb_ReopenSubKey(nn);
	//	nRet = bs_treedb_open_subkey(hHandle, nn.c_str(), TRDB_OPKF_OPENEXIST);
	//	if (nRet == BS_NOERROR)
	//	{
	//		//string szip = hLoc.Treedb_GetPropertyString("ip", "");
	//		chen::VariableData vData;			
	//		nRet = bs_treedb_get_property(hHandle, "ip", vData);
	//		if (nRet != BS_NOERROR)
	//		{
	//			cout << "bs_treedb_get_property [net.ip] Error " << nn << "[nRet]" << nRet << endl;
	//			break;;
	//		}
	//		string szip = CDbVar::VariableDataToString(vData);
	//		nRet = bs_treedb_get_property(hHandle, "mask", vData);
	//		if (nRet != BS_NOERROR)
	//		{
	//			cout << "bs_treedb_get_property [net.mask] Error " << nn << "[nRet]" << nRet << endl;
	//			break;;
	//		}
	//		string szmask = CDbVar::VariableDataToString(vData);

	//		if (szip.size() == 0 || szip.find('.') == string::npos)
	//		{
	//			index++;
	//			printf("szip error %s %s\n", nn.c_str(), szip.c_str());
	//			continue;
	//		}

	//		if (szmask.size() == 0 || szmask.find('.') == string::npos)
	//		{
	//			index++;
	//			printf("szip error %s %s\n", nn.c_str(), szmask.c_str());
	//			continue;
	//		}

	//		cnet.m_szIp = szip;
	//		cnet.m_szMask = szmask;

	//		unsigned lo = 0;
	//		unsigned hi = 0;
	//		cnet.GetIpScope3(lo, hi);
	//		netrangelst.push_back(std::make_pair(lo, hi));
	//	}
	//	else
	//	{
	//		cout << "bs_treedb_open_subkey error " << nn << "[nRet]" << nRet << endl;
	//		return;
	//	}
	//}

	//if (index != 0)
	//{
	//	cout << "index %d" << index << endl;
	//	return;
	//}

	//printf("3 CAL_ALL_Net finish %d\n", netlist.size());
	//Sleep(sleeptime);





	/////////////////////////ip
	//list<string> iplist;
	////nRet = hLoc.Treedb_ReopenSubKey(strMainIP);
	//nRet = bs_treedb_open_subkey(hHandle, strMainIP.c_str(), TRDB_OPKF_OPENEXIST);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "Treedb_ReopenSubKey Error" << "[strMainIP]" << strMainIP << "[nRet]" << nRet << endl;
	//	return;
	//}


	////nRet = hLoc.Treedb_GetAllSubKeys(iplist);
	//nRet = bs_treedb_get_subkeys(hHandle, iplist);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "bs_treedb_get_subkeys ip Error" << "[nRet]" << nRet << endl;
	//	return;
	//}

	//printf("4 GET_ALL_ip %d\n", iplist.size());
	//Sleep(sleeptime);

	//
	////hLoc.Treedb_BeginTransaction();
	//nRet = bs_treedb_begin_transaction(hHandle);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "bs_treedb_begin_transaction ip Error" << "[nRet]" << nRet << endl;
	//	return;
	//}

	//index = 0;
	//int index2 = 0;
	//int index_all = 0;
	//bool bok = true;
	//int index3 = 0;
	//int skip = 100;
	//for (auto it : iplist)
	//{
	//	++index_all;
	//	bool bdl = true;
	//	nn = strMainIP + "\\" + it;
	//	//nRet = hLoc.Treedb_ReopenSubKey(nn);
	//	nRet = bs_treedb_open_subkey(hHandle, nn.c_str(), TRDB_OPKF_OPENEXIST);;
	//	if (nRet == BS_NOERROR)
	//	{
	//		//string szip = hLoc.Treedb_GetPropertyString("ip", "");
	//		chen::VariableData vData;
	//		nRet = bs_treedb_get_property(hHandle, "ip", vData);
	//		if (nRet != BS_NOERROR)
	//		{
	//			cout << "bs_treedb_get_property [ip.ip] Error " << nn << "[nRet]" << nRet << endl;
	//			break;;
	//		}
	//		string szip = CDbVar::VariableDataToString(vData);

	//		if (szip.size() == 0 || szip.find('.') == string::npos)
	//		{
	//			printf("[%d]bad ip delete %s----------------\n", ++index, it.c_str());
	//			//nRet = hLoc.Treedb_DeleteSubKey(nn);
	//			nRet = bs_treedb_delete_key(hHandle);
	//			if (nRet != BS_NOERROR)
	//			{
	//				//bok = false;
	//				//printf("bs_treedb_delete_key error %s----------------\n", it.c_str());
	//				cout << "bs_treedb_delete_key [net] Error " << nn << "[nRet]" << nRet << endl;
	//				//break;
	//				continue;
	//			}
	//		}

	//		unsigned int  uip = 0;
	//		uip = CSSubNet::StrToInt(szip);

	//		for (auto it2 : netrangelst)
	//		{
	//			if (uip <= it2.second && uip >= it2.first)
	//			{
	//				bdl = false;
	//				break;
	//			}
	//		}

	//		if (bdl)
	//		{
	//			if (index_all % skip == 0)
	//			{
	//				printf("[%d][%d][%d]dead ip delete %s----------------\n", ++index, ++index2, index_all, nn.c_str());
	//			}
	//			//nRet = hLoc.Treedb_DeleteSubKey(nn);
	//			//nRet = hLoc.Treedb_DeleteThisKey();
	//			nRet = bs_treedb_delete_key(hHandle);
	//			if (nRet != BS_NOERROR)
	//			{
	//				//bok = false;
	//				printf("bs_treedb_delete_key error %s----------------\n", nn.c_str());
	//				//break;
	//				continue;
	//			}
	//		}
	//		//else
	//		//{
	//		//	printf("[%d]no delete    %s----------------\n", ++index3, nn.c_str());;
	//		//}
	//	}
	//	else
	//	{
	//		//bok = false;
	//		cout << "Treedb_ReopenSubKey ip error " << nn << "[nRet]" << nRet << endl;
	//		//break;
	//		continue;
	//	}
	//}

	//if (!bok)
	//{
	//	printf("clear error ----------------\n");
	//	//nRet = hLoc.Treedb_RollbackTransaction();
	//	nRet = bs_treedb_rollback_transaction(hHandle);
	//	if (nRet != BS_NOERROR)
	//	{
	//		cout << "bs_treedb_rollback_transaction ip Error" << "[nRet]" << nRet << endl;
	//		return;
	//	}
	//	bs_close_handle(hHandle);
	//	return;
	//}

	////hLoc.Treedb_CommitTransaction();
	//nRet = bs_treedb_commit_transaction(hHandle);
	//if (nRet != BS_NOERROR)
	//{
	//	cout << "bs_treedb_commit_transaction ip Error" << "[nRet]" << nRet << endl;
	//	return;
	//}
	//bs_close_handle(hHandle);
	//printf("5 clear success ----------------\n");
}


void ConfigTest(const string& file)
{
	chen::CIniFile cfg(file);
	cfg.Init();
	string strserver;
	string strco;
	string strnet;
	string strnum;
	cfg.ReadItem("main", "server", strserver);
	cfg.ReadItem("main", "co", strco);
	cfg.ReadItem("main", "net", strnet);
	cfg.ReadItem("main", "num", strnum);

	printf("[server]%s[co]%s[net]%s[num]%s\n", strserver.c_str(), strco.c_str(), strnet.c_str(), strnum.c_str());
	printf("[server]%d[co]%d[net]%d[num]%d\n", strserver.size(), strco.size(), strnet.size(), strnum.size());
}


void Config(string& server, string& co, string& net, int& num, const string& file)
{
	chen::CIniFile cfg(file);
	cfg.Init();
	string strserver;
	string strco;
	string strnet;
	string strnum;
	cfg.ReadItem("main", "server", strserver);
	cfg.ReadItem("main", "co", strco);
	cfg.ReadItem("main", "net", strnet);
	cfg.ReadItem("main", "num", strnum);


	server = strserver;
	co = strco;
	net = strnet;
	if (strnum.size() == 0)
	{
		num = 0;
	}
	else
	{
		num = atoi(strnum.c_str());
	}
	//printf("[server]%s[co]%s[net]%s[num]%s\n", server.c_str(), co.c_str(), net.c_str(), strnum.c_str());
}


void StatisticsIPNet(const string& server, const string& co, const string& net)
{
	CMxHandleLoc hLoc;
	int sleeptime = 1000;
	int sleeptime2 = 300;
	int nRet = hLoc.Treedb_Alloc(server, "ipctrl", "Co");
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error" << "[server]" << server << endl;
		return;
	}

	cout << "1 Treedb_Alloc success" << endl;
	Sleep(sleeptime);

	char tmp[100] = { 0 };
	sprintf(tmp, "%s\\Net", co.c_str());
	string strMain = tmp;
	string strMain2 = tmp;
	list<string> lstnet;
	if (net.size() == 0)
	{
		nRet = hLoc.Treedb_ReopenSubKey(strMain);
		if (nRet != BS_NOERROR)
		{
			cout << "Treedb_ReopenSubKey Error" << "[strMain]" << strMain << endl;
			return;
		}

		nRet = hLoc.Treedb_GetAllSubKeys(lstnet);
		if (nRet != BS_NOERROR)
		{
			cout << "Treedb_GetAllSubKeys Error" << "[strMain]" << strMain << endl;
			return;
		}
	}
	else
	{
		lstnet.push_back(net);
	}

	cout << "2 Treedb_GetAllSubKeys success" << endl;
	Sleep(sleeptime);

	int index = 0;
	int sumip = 0;
	int sumnet = 0;
	for (auto it : lstnet)
	{
		++index;
		sprintf(tmp, "%s\\Net\\%s", co.c_str(), it.c_str());
		strMain2 = tmp;
		string strMainNet = strMain2 + "\\SubNet";
		string strMainIP = strMain2 + "\\IP";

		nRet = hLoc.Treedb_ReopenSubKey(strMainNet);
		if (nRet != BS_NOERROR)
		{
			cout << "Treedb_ReopenSubKey Error" << "[strMainNet]" << strMainNet << endl;
			return;
		}

		list<string> lsttmpnet;
		nRet = hLoc.Treedb_GetAllSubKeys(lsttmpnet);
		if (nRet != BS_NOERROR)
		{
			cout << "Treedb_GetAllSubKeys Error" << "[strMainNet]" << strMainNet <<  endl;
			return;
		}

		nRet = hLoc.Treedb_ReopenSubKey(strMainIP);
		if (nRet != BS_NOERROR)
		{
			cout << "Treedb_ReopenSubKey Error" << "[strMainNet]" << strMainIP << endl;
			return;
		}

		list<string> lsttmpip;
		nRet = hLoc.Treedb_GetAllSubKeys(lsttmpip);
		if (nRet != BS_NOERROR)
		{
			cout << "Treedb_GetAllSubKeys Error" << "[strMainNet]" << strMainIP << endl;
			return;
		}

		printf("[%3d][%s][SubNet]%d[IP]%d\n", index, strMain2.c_str(), lsttmpnet.size(), lsttmpip.size());

		sumip += lsttmpip.size();
		sumnet += lsttmpnet.size();
				
		Sleep(sleeptime2);
	}


	printf("\n[SUM][%s][SubNet]%d[IP]%d\n\n", strMain.c_str(), sumnet, sumip);

}

void SpecialCharacter(const string& server, const string& db, const string& mainkey, const string& path)
{
	CMxHandleLoc hLoc;
	int nRet = hLoc.Treedb_Alloc(server, db, mainkey);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << endl;
		return;
	}

	nRet = hLoc.Treedb_ReopenSubKey(path, ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error!" << endl;
		return;
	}

	//string name = hLoc.Treedb_GetPropertyString("name", "");
	//double price = hLoc.Treedb_GetPropertyDouble("price", 0.0);
	//int value = hLoc.Treedb_GetPropertyInt("value", 0);
	//char type = (char)hLoc.Treedb_GetPropertyInt("type", 0);

	string value = "1234sdfDSA抽到";
	nRet = hLoc.Treedb_WriteKeyString("SpecialCharacter1", value);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_WriteKeyString Error!" << endl;
		return;
	}

	value = "！";
	nRet = hLoc.Treedb_WriteKeyString("SpecialCharacter2", value);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_WriteKeyString Error!" << endl;
		return;
	}
	value = "@";
	nRet = hLoc.Treedb_WriteKeyString("SpecialCharacter3", value);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_WriteKeyString Error!" << endl;
		return;
	}
	value = "#";
	nRet = hLoc.Treedb_WriteKeyString("SpecialCharacter4", value);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_WriteKeyString Error!" << endl;
		return;
	}
	value = "¥";
	nRet = hLoc.Treedb_WriteKeyString("SpecialCharacter5", value);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_WriteKeyString Error!" << endl;
		return;
	}
}

void writeTreeDb(const string& strServer, const string& strDb, const string& strPath, const string& strSunPath)
{
	CMxHandleLoc hLoc;
	int nRet = hLoc.Treedb_Alloc(strServer, strDb, strPath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << " strServer:" << strServer << " DB:" << strDb << endl;
		return;
	}


	nRet = hLoc.Treedb_ReopenSubKeyEx("test", ExistNodePath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error:" << "subtest2" << endl;
		return;
	}
	
	string subkey;
	// 使用 append 若没有 子健名为空 则 自动创建子健名 并以 父键.num的形式 返回
	// 如下面的则依次创建子健 test.1 test.2 test.3 test.4
	// 只要父键没有删除 数据库自己会记录一个索引递增 如 现有1 2 3子健 删除了3 剩下1 2 在append 创建4子健 即使子健都删除了 在append 则创建5子健
	nRet = hLoc.Treedb_AppendSubKey("test", subkey);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error:" << "subtest2" << endl;
		return;
	}

	subkey = "";
	nRet = hLoc.Treedb_AppendSubKey("test", subkey);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error:" << "subtest2" << endl;
		return;
	}




	// 路径名中 有 . 跟上面 有 \ 效果一样
	CMxHandleLoc hLoc2;
	nRet = hLoc2.Treedb_Alloc(strServer, strDb, strPath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_Alloc Error!" << " strServer:" << strServer << " DB:" << strDb << endl;
		return;
	}
	nRet = hLoc2.Treedb_ReopenSubKeyEx("test2", ExistDotPath);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error:" << "subtest2" << endl;
		return;
	}

	subkey = "test2.1";
	nRet = hLoc2.Treedb_AppendSubKey("test2", subkey);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error:" << "subtest2" << endl;
		return;
	}

	subkey = "test2.1";
	nRet = hLoc2.Treedb_AppendSubKey("test2", subkey);
	if (nRet != BS_NOERROR)
	{
		cout << "Treedb_ReopenSubKey Error:" << "subtest2" << endl;
		return;
	}

	////更改属性的名字 值
	//hLoc.Treedb_RenameProperty("name", "name_xx");
	//hLoc.Treedb_WriteKeyString("name_xx", "name_vvvvvv");
	//string name = hLoc.Treedb_GetPropertyString("name_xx", "");
	//double price = hLoc.Treedb_GetPropertyDouble("price", 0.0);
	//int value = hLoc.Treedb_GetPropertyInt("value", 0);
	//char type = (char)hLoc.Treedb_GetPropertyInt("type", 0);

	//cout << "name:" << name << " price:" << price << " value:" << value << " type:" << type << endl;


	cout << "-----------------" << endl;
}


