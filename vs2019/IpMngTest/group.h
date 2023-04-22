#pragma once
#include "subnet.h"

//×éÂ·¾¶ Ga\Gsa\Gssa\Gsssa
class Group	
{
public:
	void addgroup() { std::cout << "addgroup" << std::endl; }
	void modifygroup() { std::cout << "modifygroup" << std::endl; }
	void ignore(bool b) { m_ignore = b; };

	void modifysubnet(std::string str) { std::cout << "modifysubnet" << std::endl; }
	void addsubnet(std::string str) { std::cout << "addsubnet" << std::endl; }
	void getallsubnet() { std::cout << "getallsubnet" << std::endl; }
protected:
private:

public:
	std::map<std::string, SubNet> m_subnets;
	std::map<std::string, Group> m_groups;
	bool m_ignore;
	std::string m_name;
	std::string m_parent;

	std::string m_path;
};