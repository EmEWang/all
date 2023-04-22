#include <sys/utsname.h>
#include <iostream>
#include <cstdio>
#include <chrono>


#include "netfun.h"
#include "sysfun.h"
#include "strconv.h"

using namespace std;


void test1();

void test2();

void testtime();
void testtime2();

int main()
{
	printf("-----start-----\n");
	//net
	//net1("192.168.6.155", "80");

	//sys
	//testsysfun1();

	//

	//test2();

	//testtime();
	testtime2();

	printf("------end------\n");
}

void test1()
{
	auto start = std::chrono::high_resolution_clock::now();
	utsname names;
	if (uname(&names) != 0) {
		std::perror("cannot get unames");
	}

	std::cout << "Linux kernel version: " << names.release << std::endl;;
}

void test2()
{
	const char* psource = "ÏîÄ¿";
	//char psource[100] = "123";
	wstring wdes;
	string des;
	wstring wdes2;
	string des2;
	UTF8ToANSI2(psource, strlen(psource),des);
	//ANSIToUTF8(des.c_str(), des2);
	//ANSIToUnicode(psource, wdes);
	//ANSIToUnicode(psource, wdes);
	//UnicodeToUTF8(wdes.c_str(), des);
	//UTF8ToUnicode(des.c_str(), wdes2);
	//UnicodeToANSI(wdes2.c_str(), des2);

	return;
}

void testtime()
{
	time_t t = time(0);
	string str1 = ctime(&t);

	printf("time:%s\n", str1.c_str());
	printf("1111111\n");
}

void testtime2()
{
	clock_t start = clock();
	chrono::time_point<chrono::steady_clock> stp = chrono::steady_clock::now();
	sleep(3);
	clock_t end = clock();
	chrono::time_point<chrono::steady_clock> etp = chrono::steady_clock::now();
	printf("time:%d %d %lld %lld %d\n", end-start, CLOCKS_PER_SEC, start, end, chrono::duration_cast<chrono::milliseconds>(etp -stp).count());
}
