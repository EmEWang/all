#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>

using namespace std;


class ClassA
{
public:
	ClassA(int a) : _a(a)
	{}
	// ��ʽȱʡ���캯�����ɱ���������
	ClassA() = default;

	// �����������������ⶨ��ʱ�ñ���������Ĭ�ϸ�ֵ���������
	ClassA& operator=(const ClassA& a);
private:
	int _a;
};




void listinitialization(); //�б��ʼ��
void listinitialization2(); //�б��ʼ��
void listinitialization3(); //�б��ʼ��

void auto2(); //�����Ƶ�

void decltype2(); //�����Ƶ�

void for2(); //��Χforѭ��

void override2(); //ָ��һ���麯��������һ���麯��
void final2(); //ָ��ĳ���麯�������������б����ǣ�����ĳ���಻�ܱ�����̳�

void array2(); //��������������̬����array��forward_list�Լ�unorderedϵ��
void tuple2(); //tuple pair

void default2(); //Ĭ�ϳ�Ա��������

void threadpool(); //�̳߳�


