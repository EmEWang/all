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


bool curlexample1();     //��ȡ��Ӧд���ļ� û��дȫ
bool curlexample2();     //��ȡ��Ӧд���ļ� дȫ
bool curlexample3();     //��ȡ��Ӧд���ļ� дȫ ͬ��Ҳдheader�ļ�


