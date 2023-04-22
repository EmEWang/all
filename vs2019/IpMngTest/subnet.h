#pragma once
#include <map>
#include <algorithm>

#include "ip.h"

class SubNet
{
public:
	SubNet();
	~SubNet();

	void getallip() { std::cout << "getallip" << std::endl; }
	void modifysubnet() { std::cout << "modifysubnet" << std::endl; }
	bool ignore(bool b) { m_ignore = b; }

	//ipµÄÔöÉ¾
	void addip(std::string ip) { m_ips[ip] = Ip(ip); }
	void delip(std::string ip) { m_ips.erase(ip); }

private:

public:	
	std::map<std::string, Ip> m_ips;
	std::string m_name;
	std::string m_parent;
	bool m_ignore;

};

SubNet::SubNet()
{
}

SubNet::~SubNet()
{
}
