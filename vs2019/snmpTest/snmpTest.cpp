// snmpTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include "snmp_pp/snmp_pp.h"
//#include "snmp_pp/snmperrs.h"
//#include "snmp_pp/snmpmsg.h"
//#include "snmp_pp/octet.h"

std::string getVbValue(Vb& vb);
int testConnected(Snmp* pSnmp, UdpAddress* pAddr);
SnmpTarget* makeTarget(Snmp* pSnmp, UdpAddress* pAddr, CTarget& ctarget, UTarget& utarget, int version, int nVlanIndex = -1);
int getNextTarget(Snmp* pSnmp, SnmpTarget* target,
	std::string strOid, std::string& strNextOid, std::string& strNextVal
	, int nVersion, int securityLevel, OctetStr contextName, OctetStr contextEngineID);
void getValue(std::string strIp, int nPort, std::string strOid);
void getValue2(std::string strIp, int nPort, std::string strOid);
void getValueNext2(std::string strIp, int nPort, std::string strOid);

int main()
{
    std::cout << "Hello World!\n";
	//1.3.6.1.2.1.1.1
	getValue2("192.168.6.155", 161, "1.3.6.1.2.1.1.1");
	getValue2("192.168.6.155", 161, "1.3.6.1.2.1.1.4.0");
	getValueNext2("192.168.6.155", 161, "1.3.6.1.2.1.1.4.0");


	getValue("192.168.6.155", 161, "1.3.6.1.2.1.1.4.0");

	

    system("pause");
}

void getValue(std::string strIp, int nPort, std::string strOid)
{
	Snmp::socket_startup();
	snmp_version version = version2c;
	int status = 0;
	Snmp snmp(status, 0, false);
	if (status != SNMP_CLASS_SUCCESS) {
		printf("SNMP++ Session Create Fail, %s\r\n", snmp.error_msg(status));
		return;
	}

	UdpAddress address(strIp.c_str());
	if (address.valid())
	{
		address.set_port(nPort);

		if (testConnected(&snmp, &address)) {
			return;
		}

		CTarget ctarget(address);             // make a target using the address
		UTarget utarget(address);
		SnmpTarget* target = makeTarget(&snmp, &address, ctarget, utarget, 1);

		std::string strNextOid;
		std::string strNextVal;
		int nVersion =1;
		int securityLevel = 0;
		OctetStr contextName;
		OctetStr contextEngineID;

		int nSleep = 10 * 1000;
		getNextTarget(&snmp, target, strOid, strNextOid, strNextVal, nVersion, securityLevel, contextName, contextEngineID);
	}

	Snmp::socket_cleanup();
}

SnmpTarget* makeTarget(Snmp* pSnmp, UdpAddress* pAddr, CTarget& ctarget, UTarget& utarget, int version, int nVlanIndex)
{

	SnmpTarget* target = NULL;
	std::string strRComm = "public";
	OctetStr community(strRComm.c_str());           // community name
	ctarget.set_version((snmp_version)version);         // set the SNMP version SNMPV1 or V2
	ctarget.set_retry(2);           // set the number of auto retries
	ctarget.set_timeout(100);         // set timeout
	ctarget.set_readcommunity(community); // set the read community name
	target = &ctarget;
	return target;
}


int testConnected(Snmp* pSnmp, UdpAddress* pAddr)
{
	std::string strNxtOid = "";
	std::string strNxtVal = "";

	CTarget ctarget(*pAddr);             // make a target using the address
	UTarget utarget(*pAddr);
	SnmpTarget* target = makeTarget(pSnmp, pAddr, ctarget, utarget, 1);

	std::string strOid;
	std::string strNextOid;
	std::string strNextVal;
	int nVersion;
	int securityLevel;
	OctetStr contextName;
	OctetStr contextEngineID;

	int bRet = getNextTarget(pSnmp, target,"1.3.6.1.2.1.1.1", strNxtOid, strNxtVal
		,1 , 0, "", "");
	if (bRet)
	{
		printf("%d-%s", bRet, strNxtVal.c_str());
	}
	return bRet;
}



int getNextTarget(Snmp* pSnmp, SnmpTarget* target,
	std::string strOid, std::string& strNextOid, std::string& strNextVal
	, int nVersion, int securityLevel, OctetStr contextName, OctetStr contextEngineID)
{
	Pdu pdu;                              // construct a Pdu object
	Vb vb;
	Oid oid(strOid.c_str());
	vb.set_oid(oid);
	pdu += vb;                            // add the vb to the Pdu

	if (nVersion == version3)
	{
		pdu.set_security_level(securityLevel);
		pdu.set_context_name(contextName);
		pdu.set_context_engine_id(contextEngineID);
	}

	int status = SNMP_CLASS_SUCCESS;
	if ((status = pSnmp->get_next(pdu, *target)) == SNMP_CLASS_SUCCESS)
	{
		pdu.get_vb(vb, 0);
		if (pdu.get_type() == REPORT_MSG) {
			strNextVal = pSnmp->error_msg(vb.get_printable_oid());
			return FALSE;
		}
		if ((vb.get_syntax() != sNMP_SYNTAX_ENDOFMIBVIEW)
			|| (vb.get_syntax() != sNMP_SYNTAX_NOSUCHINSTANCE)
			|| (vb.get_syntax() != sNMP_SYNTAX_NOSUCHOBJECT))
		{

			strNextOid = vb.get_printable_oid();
			strNextVal = getVbValue(vb);
		}
		else
			return FALSE;
	}
	else
	{
		strNextVal = pSnmp->error_msg(status);
		return FALSE;
	}
}


std::string getVbValue(Vb& vb)
{
	std::string  szOid = vb.get_printable_oid();
	OctetStr val;
	int nRet = vb.get_value(val);
	if (nRet == SNMP_CLASS_SUCCESS)
	{
		printf("vb.get_value(val) is SNMP_CLASS_SUCCESS\n");
		return val.get_printable_hex();
	}
	else
		return vb.get_printable_value();
}

void getValue2(std::string strIp, int nPort, std::string strOid)
{
	Snmp::socket_startup();//初始化Winsocket套接字
	snmp_version version = version2c;
	int status;
	Snmp  snmp(status, 0, false);//创建一个snmp对象
	Pdu pdu;//创建一个pdu对象
	Vb vb;//创建一个vb对象
	vb.set_oid((Oid)strOid.c_str());
	pdu += vb;//设置vb对象并将其添加到对象pdu中
	//UdpAddress  address("192.168.6.155:161");
	UdpAddress  address(strIp.c_str());
	if (address.valid())
	{
		address.set_port(nPort);
	}
	CTarget  ctarget(address);//创建一个ctarget对象
	ctarget.set_version(version);
	ctarget.set_retry(1);
	ctarget.set_timeout(100);
	ctarget.set_readcommunity("public");//设置ctarget对象
	SnmpTarget* target;
	target = &ctarget;
	status = snmp.get(pdu, *target);//发起一个Get操作
	if (status == SNMP_CLASS_SUCCESS)
	{
		pdu.get_vb(vb, 0);
		std::string reply_oid = vb.get_printable_oid();
		//std::string reply_value = vb.get_printable_value();
		OctetStr val;
		std::string strval;
		int nRet = vb.get_value(val);
		if (nRet == SNMP_CLASS_SUCCESS)
		{
			//printf("vb.get_value(val) is SNMP_CLASS_SUCCESS\n");
			strval =  val.get_printable_hex();
		}
		else
			strval = vb.get_printable_value();

		printf("[oid]%s[value]\n%s\n", reply_oid.c_str(), strval.c_str());
	}//操作成功，将被管理对象的OID和值保存到reply_oid和reply_value中。

	Snmp::socket_cleanup();
}

void getValueNext2(std::string strIp, int nPort, std::string strOid)
{
	Snmp::socket_startup();//初始化Winsocket套接字
	snmp_version version = version2c;
	int status;
	Snmp  snmp(status, 0, false);//创建一个snmp对象
	Pdu pdu;//创建一个pdu对象
	Vb vb;//创建一个vb对象
	vb.set_oid((Oid)strOid.c_str());
	pdu += vb;//设置vb对象并将其添加到对象pdu中
	//UdpAddress  address("192.168.6.155:161");
	UdpAddress  address(strIp.c_str());
	if (address.valid())
	{
		address.set_port(nPort);
	}
	CTarget  ctarget(address);//创建一个ctarget对象
	ctarget.set_version(version);
	ctarget.set_retry(1);
	ctarget.set_timeout(100);
	ctarget.set_readcommunity("public");//设置ctarget对象
	SnmpTarget* target;
	target = &ctarget;
	status = snmp.get_next(pdu, *target);//发起一个Get操作
	if (status == SNMP_CLASS_SUCCESS)
	{
		pdu.get_vb(vb, 0);
		std::string reply_oid = vb.get_printable_oid();
		std::string reply_value = vb.get_printable_value();

		printf("[oid]%s[value]%s\n", reply_oid.c_str(), reply_value.c_str());
	}//操作成功，将被管理对象的OID和值保存到reply_oid和reply_value中。

	Snmp::socket_cleanup();
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
