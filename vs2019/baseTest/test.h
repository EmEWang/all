#pragma once
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <map>

#include "VariableData.h"
#include "DbVar.h"
#include "MemCache.h"
#include "TimeFace.h"
//test ������
// CDbVar::SerialString  CDbVar::SerialVar  CDbVar::UnSerialVar

void testvar();








//test che::variable ��Ҫ��2��ģʽ ����ģʽ �� bitģʽ
// ����ģʽ ��������� �໥��ֵ ת�� �ַ� ���� ���� c�ַ��� ע��: �ַ���ָ��ֻ�Ǹ�������ָ�� ��û�з����ڴ�
// 1��char * SerialData(char *data,int *len) variable���л� ���� data ���л���Ŀ�ĵ�ַ len ���뻺�������� �������л��ĳ��� ����ֵ ���л���Ŀ�ĵ�ַ
// ��ʽΪ 1����ģʽ ��һ���ֽ����� Ȼ���ǻ������͵����� ����c����ַ�������ԭ�����
//        2bitģʽ  ��һ���ֽ����� Ȼ���� 4���ֽ�bit���� Ȼ���� bit�ֽ�
// 2��Size() ����variable���л���Ҫ���ֽ���
// 3��bool UnSerial(const char *data,int len) variable�����л� ���� data �����л���Դ���ݵ�ַ len ���������� ����ֵ �Ƿ�ɹ�
// Ҳ����˵ �������һ��variable����
// 4��bool PutBinData(const char *data,int len,bool isAllocMem=true); bitģʽ��ֵ len��ǳ��� ��Դ����data ���� variable ��
// 5��bool GetBinData(char* buf, int& len);  bitģʽȡֵ ��variable������data ���� buf��
// 6��char * SerialDataByByteOrder(char *data,int *len) const;    �ֽ��� ���л�
// 7) bool UnSerialByByteOrder(const char* data, int len);        �ֽ������л�
// 8) bool PutTimeValue(time_t ttm);                              ����ʱ��
// 9) bool GetTimeValue(time_t& ttm) const;                       ȡ��ʱ��
void testchenvariable();



void testchenMemCache();
void testchenTimeFace();