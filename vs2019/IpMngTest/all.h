#pragma once
#include "net.h"


//全路径格式
// 
// all\net\group\group\group\group...\subnet\ip
// map->map->map->                    map			内存格式
//			组的key为组的路径名
//   DB格式
//	all
//		net
//			group	(group\group\group\group)
//			group
//			group
//				subnet
//				subnet
//				subnet
//					ip
//					ip
//					ip
// 
//		net
class All
{
public:
	All();
	~All();

	void getallnet() { std::cout << "getallnet" << std::endl; }
	void addnet() { std::cout << "addnet" << std::endl; }
	void removenet() { std::cout << "removenet" << std::endl; }
	void getts() { std::cout << "getts" << std::endl; }
	void ignore(bool b) { m_ignore = b; };

	

private:
	std::map<std::string, Net> m_nets;
	bool m_ignore;
	std::string m_name;


	//
public:
	std::map<string, Net> m_m_net;

};

All::All()
{
}

All::~All()
{
}