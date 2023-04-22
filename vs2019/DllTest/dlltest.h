#pragma once

#include <stdio.h>
#include <stdlib.h>

#define DLL_EXPORT

#ifdef DLL_EXPORT
#define ZZZAPI   __declspec(dllexport)
#else
#define ZZZAPI   __declspec(dllimport)
#endif


ZZZAPI void telldll1();
ZZZAPI void telldll2();
ZZZAPI void telldll3();
__declspec(dllexport) void telldll4();

//class ZZZAPI AAA
//{
//public:
//	void testAAA1() { printf("111"); }
//	void testAAA2() { printf("111"); }
//protected:
//private:
//};
//
//class ZZZAPI BBB
//{
//public:
//	void testBBB1() { printf("111"); }
//	void testBBB2() { printf("111"); }
//protected:
//private:
//};