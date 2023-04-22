#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>

#include<algorithm>                 // �㷨
#include <functional>               // �º���
#include <numeric>                  // 
#include <memory>                  // 

using namespace std;

void map1();

void insertIterator();    // 1)for (auto val in col) �� val��ֵ����it 2)ʹ�ø�ֵ ����ʹ��*it(��������) ����ʹ�� it
void insertIteratorOut(); // 1)cout ����ֱ����� it ������� *it
void insertFunc1(); // 1)�º���
void testmap();    //��map��û�ж�Ӧ��key ���ؿ� ��valueΪָ�� ΪNULL
void testlist();
void testlist2();
void testlist3();   // ɾ��ָ������ ���Ƿ��������
void testlist4();   //ָ���ȽϷ���
void OstreamInterator();
void testtransform();

void testlamda();

void testfor_each();
void testcount();
void testminmax();
void testfindsearch();
void testSection();
void testModify();
void testNumber();

void testshareptr();
void testuniqueptr();
void testweakptr();


// ʱ��
#include <chrono>
void testtime1();
void testtime2();
void testtime3();
void testtime4();
void testtime5();  //std::put_time()��


// �߳�
#include <thread>
void testthread1();
#include <mutex>
void testthread2();
void testthread3();
void testthread4();


// ����
#include <regex>
void testregex1();
void testregex2();
void testregex3();
void testregex4();

//hash_map
#define 	_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>
#include <unordered_map>
void testhashmap();


// float
#include <cfloat>
void testfloat1();

