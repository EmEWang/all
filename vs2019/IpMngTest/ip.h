#pragma once
#include <string>
#include <list>

using namespace std;

class Ip
{
public:
	//пехн пч╦д
	void trust(bool t = true) { m_trust = t; }
	bool istrst() { return m_trust; }
	void modify(const std::string& str) { m_ipdetail = str; }


	Ip(){}
	Ip(std::string ip):m_name(ip) {}
protected:
private:

public:
	std::string m_name;
	bool m_trust;

	std::string m_ipdetail;

	string m_ip;
	string m_port;
};