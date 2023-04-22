#pragma once

#include <iostream>

#include "curl.h"
using namespace std;



bool curlinit();
bool curlfill();
bool curlget();
bool curlpost();
bool curlsend();
bool curlclear();


bool curlexample1();     //获取相应写入文件 没有写全
bool curlexample2();     //获取相应写入文件 写全
bool curlexample3();     //获取相应写入文件 写全 同样也写header文件


