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
//test 公共库
// CDbVar::SerialString  CDbVar::SerialVar  CDbVar::UnSerialVar

void testvar();








//test che::variable 主要有2中模式 基本模式 和 bit模式
// 基本模式 与基本类型 相互赋值 转换 字符 整数 浮点 c字符串 注意: 字符串指针只是个单纯的指针 并没有分配内存
// 1）char * SerialData(char *data,int *len) variable序列化 参数 data 序列化的目的地址 len 输入缓冲区长度 返回序列化的长度 返回值 序列化的目的地址
// 格式为 1基本模式 第一个字节类型 然后是基本类型的数据 其中c风格字符串还是原来风格
//        2bit模式  第一个字节类型 然后是 4个字节bit长度 然后是 bit字节
// 2）Size() 返回variable序列化需要的字节数
// 3）bool UnSerial(const char *data,int len) variable反序列化 参数 data 反序列化的源数据地址 len 缓冲区长度 返回值 是否成功
// 也就是说 最后生成一个variable对象
// 4）bool PutBinData(const char *data,int len,bool isAllocMem=true); bit模式赋值 len标记长度 把源数据data 放入 variable 中
// 5）bool GetBinData(char* buf, int& len);  bit模式取值 把variable中数据data 放入 buf中
// 6）char * SerialDataByByteOrder(char *data,int *len) const;    字节序 序列化
// 7) bool UnSerialByByteOrder(const char* data, int len);        字节序反序列化
// 8) bool PutTimeValue(time_t ttm);                              放入时间
// 9) bool GetTimeValue(time_t& ttm) const;                       取出时间
void testchenvariable();



void testchenMemCache();
void testchenTimeFace();