#include "test.h"


void testvar()
{
	;
}

void testchenvariable()
{
	chen::VariableData vd;
	chen::VariableData vd2;
	chen::VariableData vd3;
	char buff[40] = "1234567890";
	char buff2[40] = {0};
	char xx[40] = { 0 };
	int i = 1;
	char c = 'a';
	float f = 1.1f;
	double d = 1.1;
	long long ll = 11;
	std::string str = "abc";

	int i2 = 0;
	char c2 = ' ';
	float f2 = 2.2f;
	double d2 = 2.2;
	long long ll2 = 22;
	std::string str2 = "";

	int lenth = 0;
	int len = 0;
	int len2 = 0;
	char* cc = NULL;


	//1 基本类型 相互转换
	vd3 = 33;
	int i3 = vd3;
	vd3 = 33.22f;
	float f3 = vd3;
	vd3 = 33.33;
	double d3 = vd3;
	vd3 = 'c';
	char c3 = vd3;
	long long ll3 = 0;

	// 基本 类型 序列化 与反序列化
	len = sizeof(buff) / sizeof(char);
	vd = str.c_str();	
	lenth = vd.Size();
	cc = vd.SerialData(xx, &len);
	len = sizeof(buff) / sizeof(char);
	vd2.UnSerial(xx, len);
	str2 = (char*)vd2;

	len = sizeof(buff) / sizeof(char);
	vd = i;
	lenth = vd.Size();
	cc = vd.SerialData(xx, &len);
	len = sizeof(buff) / sizeof(char);
	vd2.UnSerial(xx, len);
	i2 = vd2;

	len = sizeof(buff) / sizeof(char);
	vd = c;
	lenth = vd.Size();
	cc = vd.SerialData(xx, &len);
	len = sizeof(buff) / sizeof(char);
	vd2.UnSerial(xx, len);
	c2 = vd2;

	len = sizeof(buff) / sizeof(char);
	vd = f;
	lenth = vd.Size();
	cc = vd.SerialData(xx, &len);
	len = sizeof(buff) / sizeof(char);
	vd2.UnSerial(xx, len);
	f2 = vd2;
	
	len = sizeof(buff) / sizeof(char);
	vd = d;
	lenth = vd.Size();
	cc = vd.SerialData(xx, &len);
	len = sizeof(buff) / sizeof(char);
	vd2.UnSerial(xx, len);
	d2 = vd2;

	len = sizeof(buff) / sizeof(char);
	vd = ll;
	lenth = vd.Size();
	cc = vd.SerialData(xx, &len);
	len = sizeof(buff) / sizeof(char);
	vd2.UnSerial(xx, len);
	ll2 = vd2;

	//bin模式 
	len = sizeof(buff) / sizeof(char);
	vd.PutBinData(buff, 6);
	lenth = vd.Size();
	cc = vd.SerialData(xx, &len);
	len = sizeof(buff) / sizeof(char);
	vd2.UnSerial(xx, len);
	vd2.GetBinData(buff2, len);


	len = sizeof(buff) / sizeof(char);
	vd.PutBinData((char*)&ll, sizeof(ll));
	lenth = vd.Size();
	cc = vd.SerialData(xx, &len);
	len = sizeof(buff) / sizeof(char);
	vd2.UnSerial(xx, len);
	ll3 = 0;
	len = sizeof(buff) / sizeof(char);
	vd2.GetBinData((char*)&ll3, len);

	len = sizeof(buff) / sizeof(char);
	vd.PutBinData((char*)&d, sizeof(d));
	lenth = vd.Size();
	cc = vd.SerialData(xx, &len);
	len = sizeof(buff) / sizeof(char);
	vd2.UnSerial(xx, len);
	d3 = 0.0;
	len = sizeof(buff) / sizeof(char);
	vd2.GetBinData((char*)&d3, len);

	len = sizeof(buff) / sizeof(char);
	vd.PutBinData(str.c_str(), str.size());
	lenth = vd.Size();
	cc = vd.SerialData(xx, &len);
	len = sizeof(buff) / sizeof(char);
	vd2.UnSerial(xx, len);
	ll3 = 0;
	len = sizeof(buff) / sizeof(char);
	vd2.GetBinData(buff2, len);

	// char* SerialDataByByteOrder(char* data, int* len) const;
	// bool UnSerialByByteOrder(const char* data, int len);
	len = 40;
	vd = 0x12345678;
	vd.SerialDataByByteOrder(buff2, &len);
	vd2.UnSerialByByteOrder(buff2, 40);
	
	 
	// 相当于操作整数
	// bool PutTimeValue(time_t ttm);             ttm放入variable 
	// bool GetTimeValue(time_t& ttm) const;      variable取time仿佛ttm	
	time_t tt1 = time(0);
	time_t tt2 = 0;
	vd.PutTimeValue(tt1);
	vd.GetTimeValue(tt2);
	
}

void testchenMemCache()
{
	int len = 0;
	chen::MemCache cache;
	chen::MemCache cache2;
	len = cache.Length();
	cache.AllocMem(10);
	len = cache.Length();

	cache.ZeroMem();
}

void testchenTimeFace()
{
	chen::TimeFace time1;
	chen::TimeFace time2;

}
