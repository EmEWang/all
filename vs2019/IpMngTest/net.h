#pragma once
#include "group.h"
#include "ts.h"

class Net
{
public:
	void getallgroup() { std::cout << "getallgroup" << std::endl; }
	void getallgroup(bool fileter) { std::cout << "getallgroup fileter" << std::endl; }
	void modifygroup() { std::cout << "modifygroup" << std::endl; }
	void ignore(bool b) { m_ignore = b; };
	void getsubnet(){ std::cout << "getsubnet" << std::endl; }

	void addgroup() { std::cout << "addgroup" << std::endl;  }
	void  getallungroupsubnet() { std::cout << "getallungroupsubnet" << std::endl; }
protected:
private:
	std::map<std::string, Group> m_groups;
	bool m_ignore;
	std::string m_name;


public:
	//
	std::map<string, Group> m_m_group;
	std::map<string,Ip> m_m_ip;
	std::map<string, SubNet> m_m_subnet;
	std::map<string, Ts> m_m_ts;

};