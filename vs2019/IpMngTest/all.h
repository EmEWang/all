#pragma once
#include "net.h"


//ȫ·����ʽ
// 
// all\net\group\group\group\group...\subnet\ip
// map->map->map->                    map			�ڴ��ʽ
//			���keyΪ���·����
//   DB��ʽ
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