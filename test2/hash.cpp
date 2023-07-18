//测试 stdl hash ubuntu 20.04

#include <stdio.h>
#include <iostream>
#include <string>

#include <hash_map>
#include <hash_set>

#include <unordered_map>
#include <unordered_set>

using namespace std;
using namespace __gnu_cxx;   //hash_map hash_multimap hash_set hash_multiset在这里

void simple();
void selfdef();

// hash_map unordered_map 本质是一样的，只不过 unordered_map被纳入了C++标准库标准。
// unordered_map 在头文件 unordered_map 在空间 std
// hash_map 在头文件 hash_map 在空间 __gnu_cxx



int main()
{
    simple();
    selfdef();

    return 0;
}

void simple()
{
    //hash_multimap
    hash_map<int, string> hsm;
    hsm[1] = "a";
    hsm[2] = "ab";
    hsm[3] = "abc";
    hsm[4] = "abcd";
    printf("hsm size %lu buck %lu\n", hsm.size(), hsm.bucket_count());

    //hash_multiset
    hash_set<int> hss;
    hss.insert(1);
    hss.insert(2);
    hss.insert(3);
    hss.insert(4);
    printf("hss size %lu buck %lu\n", hss.size(), hss.bucket_count());

    unordered_map<int, string> uom;
    uom[1] = "a";
    uom[2] = "ab";
    uom[3] = "abc";
    uom[4] = "abcd";
    printf("uom size %lu buck %lu\n", uom.size(), uom.bucket_count());

    unordered_set<int> uos;
    uos.insert(1);
    uos.insert(2);
    uos.insert(3);
    uos.insert(4);
    printf("uos size %lu buck %lu\n", uos.size(), uos.bucket_count());
}


struct ty1{
    int i;
    int j;
    ty1():i(0),j(0){}
    ty1(int a, int b):i(a),j(b){}
};

struct hash1{
    size_t operator () (const ty1 &t) const {return size_t(t.i);}
};

struct equal1{
    bool operator () (const ty1 &t1, const ty1 &t2) const {return t1.i == t2.i;}
};

void selfdef()
{
    typedef hash_map<ty1, string, hash1, equal1> myhsm;
    myhsm hsm;
    hsm[ty1(1,2)] = "a";
    hsm[ty1(2,2)] = "b";
    printf("hsm size %lu buck %lu\n", hsm.size(), hsm.bucket_count());
    printf("hsm find %s\n", hsm.find(ty1(2,2))->second.c_str());    //查找

    typedef hash_set<ty1, hash1, equal1> myhss;
    myhss hss;
    hss.insert(ty1(1,2));
    hss.insert(ty1(2,2));
    printf("hss size %lu buck %lu\n", hss.size(), hss.bucket_count());

    typedef unordered_map<ty1, string, hash1, equal1> myuom;
    myuom uom;
    uom[ty1(1,2)] = "a";
    uom[ty1(2,2)] = "b";
    printf("uom size %lu buck %lu\n", uom.size(), uom.bucket_count());

    typedef unordered_set<ty1, hash1, equal1> myuos;
    myuos uos;
    uos.insert(ty1(1,2));
    uos.insert(ty1(2,2));
    printf("uos size %lu buck %lu\n", uos.size(), uos.bucket_count());
}



