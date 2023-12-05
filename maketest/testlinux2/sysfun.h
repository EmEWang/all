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
const char* get_items(const char* buffer, unsigned int item);
inline unsigned long get_cpu_total_occupy();
inline unsigned long get_cpu_proc_occupy(int pid);
float GetCpuUsageRatio(int pid);
float GetMemoryUsage(int pid);


void execshell(string process);        // system
void execshell2(string process);       // popen
void execshell3(string process);       // exec
int getpidbyname(string process);      //popen方式
string getpidbyname2(string process);  //匿名管道
void testsysfun1();



