#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <string.h>

#ifdef WIN32
#include <windows.h>  
#include <psapi.h>  
//#include <tlhelp32.h>
#include <direct.h>
#include <process.h>
#else
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <unistd.h>
#endif

using namespace std;
int GetCurrentPid();
static const char* get_items(const char* buffer, unsigned int item);
static inline unsigned long get_cpu_total_occupy();
static inline unsigned long get_cpu_proc_occupy(int pid);
float GetCpuUsageRatio(int pid);
float GetMemoryUsage(int pid);


void execshell(string process);        // system
void execshell2(string process);       // popen
void execshell3(string process);       // exec
void execshell(string process);        // system
int getpidbyname(string process);      //popen��ʽ
string getpidbyname2(string process);  //�����ܵ�
void testsysfun1();



