#pragma once


#include <iostream>
#include <string>
#include <WinSock2.h>
#include <windows.h>

#include "MxHandlePool.h"
#include "chen\\IniFile.h"
#include <stdlib.h>
//#include <windows.h>
#include <utility>

#include "D:\\Code\\webwork_new\\DbWork\\IpControlDb.h"
#include "D:\\Code\\webwork_new\\ServerData\\ipmgm\\group.h"

#include <fstream>


using namespace std;

void getFromTreeDb(const string& strServer, const string& strDb, const string& strPath, const string& strSunPath );
void setToTreeDb(const string& strServer, const string& strDb, const string& strPath, const string& strSunPath);

void init(const string& strServer, const string& strFile, const string& strMainKey, const string& strSubKey);
void readkey(CMxHandleLoc &hLoc, int length, string path, const string& strServer = "", const string& strFile = "");
void readinit(const string& strServer, const string& strFile, const string& strMainKey, const string& strSubKey);

void clear(const string& strServer, const string& strFile, const string& strMainKey, const string& strSunPath);

void testPath();

void testInsertExistSubkey(const string& strServer, const string& strDb, const string& strPath);

void readint();
void editint();


void sendMq(const string& server, const string& name);
void sendMq2(const string& server, const string& name);
void getMq2(const string& server, const string& name);

void sendMq3(const string& server, const string& name, const string& label, const string& file);

void testInterface(const string& strServer, const string& strPath);

void testBableDB(const string& server, const string& table, const string &tablename);


void testKeyExist(const string& server, const string& db, const string& mainkay, const string& subkey);
void testKeyPropertyExist(const string& server, const string& db, const string& mainkey, const string& subkey, const string& property);



void testTableDB(const string& server, const string& DB, const string& table, const string& field);

void testTableDBInsert(const string& server, const string& DB, const string& table);

void ConfigTest(const string& file = "config.ini");
void Config(string& server, string& co, string& net, int& num, const string& file = "config.ini");
void ClearIP(const string& server, const string& co, const string& net);
void ClearIPOnce(const string& server, const string& co, const string& net);
void ClearIP2(const string& server, const string& co, const string& net);
void StatisticsIPNet(const string& server, const string& co, const string& net = "");

void SpecialCharacter(const string& server, const string& db, const string& mainkey , const string& path = "");

void writeTreeDb(const string& strServer, const string& strDb, const string& strPath, const string& strSunPath);
