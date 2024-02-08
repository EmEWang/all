#ifndef __MODULE2_H__
#define __MODULE2_H__


int sub(int a, int b);

#pragma once

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>


//常用头文件
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//常用常量
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define SUCCESS 1
#define UNSUCCESS -1

//常用类型定义
typedef int Status;

// 树数据类型
typedef int TElemType;

// 二叉树结构体
typedef struct BiTNode {
    TElemType data;
    struct BiTNode* lchild, * rchild;
} BiTBode, * BiTree;

// 部分需要的接口
// 将二叉树分为根，左子树，右子树三个部分
Status BreakBiTree(BiTree& T, BiTree& L, BiTree& R);
// 获取树的深度
int BiTreeDepth(BiTree T);

#ifdef __linux__
void gotoxy(int x, int y);
#else
#include <Windows.h>
//改变光标位置
void gotoxy(int x, int y);
#endif

/*
* 递归打印打印出树形
* T        正在打印的树
* depth    目前在打印树的第几层
* right    该子树是否为右子树
* tap    目前子树需要的相对偏移数量
*/
Status Traverse_R(BiTree T, int depth, int right, int tap);

// 打印树形接口
Status Traverse(BiTree T);

namespace wjg {

    template <class type>
    class node_t
    {
    public:
        type m_key;

        node_t();
    };

    template <class type>
    class node_t_b :public node_t<type>
    {
    public:
        node_t_b* m_left;
        node_t_b* m_right;

        node_t_b();
    };


    template <class type>
    class node_t_b_avl :public node_t_b<type> {
    public:
        int m_balance;

        node_t_b_avl();
    };



    template <class type>
    class tree
    {
    public:
        tree();
        bool virtual insert(type key);
        bool virtual erase(type key);
        bool virtual clear();
        int virtual size();
        int virtual depth();
        virtual node_t<type>* next();

    //private:
        node_t<type> *m_root;
        node_t<type> *m_cur;
        int m_size;
        int m_depth;
    };



    template <class type>
    class tree_b : public tree<type>
    {
    public:
        tree_b();
        bool insert(type key);
        bool erase(type key);
        bool clear();
        int size();
        int depth();
        node_t<type>* next();

    private:
        //node_t<type>* m_head;
        //node_t<type>* m_cur;
        //int m_size;
    };


    template <class type>
    class tree_b_avl : public tree_b<type>
    {
    public:
        tree_b_avl();
        bool insert(type key);
        bool erase(type key);
        bool clear();
        int size();
        int depth();
        node_t<type>* next();

    private:
        //node_t<type>* m_head;
        //node_t<type>* m_cur;
        //int m_size;
    };




    struct node_simple {
        int key;
        struct node_simple* left;
        struct node_simple* right;
        int weight;

        node_simple():key(0), left(NULL), right(NULL), weight(1){}
        node_simple(int i) :key(i), left(NULL), right(NULL), weight(1) {}
    };

//#include <stdio.h>
    class tree_simple_avl
    {
    public:
        tree_simple_avl();

        node_simple* insert(node_simple * node, node_simple* root , bool rebuild = true);
        node_simple* insert(node_simple* root, int key);
        node_simple* remove(node_simple* root, int key);
        bool insert(int node, bool rebuild);
        bool insert(int node);
        node_simple* erase(node_simple* root, int key);
        node_simple* erase(int key);
        node_simple* ll_rotate(node_simple* xnode);
        node_simple* rr_rotate(node_simple* xnode);
        node_simple* lr_rotate(node_simple* xnode);
        node_simple* rl_rotate(node_simple* xnode);
        int height(node_simple* node);
        int balance(node_simple* node);
        void print(node_simple* node, int len = 3, int skip = 1, float x = 0, int y = 0, float step = 0);
        int print(int y = 0, bool clear = true);
        node_simple* minValueNode(node_simple* root);
        void preoder(node_simple* node);
        void preoder();
        void midoder(node_simple* node);
        void midoder();
        void postoder(node_simple* node);
        void postoder();

        void print2();
        void print2(node_simple* node, char** strmap, int len, int skip, float x, int y, float step);


        int bfs(node_simple* root);
        int dfs(node_simple* root);

        node_simple* m_root;
        //int m_depth;
        //int m_depth_l;
        //int m_depth_r;
    };


    class tree_simple_avl2
    {
    public:
        tree_simple_avl2();

        bool insert(BiTBode* node);
        bool insert(int node);
        bool erase();
        bool ll_rotate();
        bool rr_rotate();

        void print(BiTBode* node = NULL);

        //int bfs(node_simple* root);
        //int dfs(node_simple* root);

        BiTBode* m_root;
    };


}





//test
inline void test2_data_1_tree()
{
    wjg::tree_simple_avl2 tree2;

    tree2.insert(1);
    tree2.insert(2);
    tree2.insert(3);
    tree2.insert(4);
    tree2.insert(5);

    tree2.print();
}
inline void test2_data_1_tree2()
{
    wjg::tree_simple_avl2 tree2;

    tree2.insert(13);
    tree2.insert(6);
    tree2.insert(1);
    tree2.insert(8);
    tree2.insert(5);

    tree2.insert(23);
    tree2.insert(15);
    tree2.insert(26);
    tree2.insert(17);
    tree2.insert(22);
    tree2.insert(21);

    tree2.print();
}
inline void test2_data_1_tree3()
{
    wjg::tree_simple_avl tree2;
    int y = 0;
    //printf("123321\n");
    tree2.insert(13);
    tree2.insert(6);
    tree2.insert(16);
    tree2.insert(1);
    tree2.insert(8);
    tree2.insert(5);

    tree2.insert(23);
    tree2.insert(15);
    tree2.insert(26);
    tree2.insert(17);
    tree2.insert(22);
    tree2.insert(21);


    tree2.insert(31);
    tree2.insert(32);
    tree2.insert(33);
    tree2.insert(34);
    tree2.insert(35);
    tree2.insert(36);

    tree2.insert(41);
    tree2.insert(42);
    tree2.insert(43);
    tree2.insert(44);
    tree2.insert(45);
    tree2.insert(46);

    tree2.insert(51);
    tree2.insert(52);
    tree2.insert(53);
    tree2.insert(54);
    tree2.insert(55);
    tree2.insert(56);

    y = tree2.print(y+1);


    tree2.erase(41);

    y += tree2.print(y+1, false);

    tree2.erase(42);

    y += tree2.print(y+1, false);


    tree2.erase(43);
    tree2.erase(44);
    tree2.erase(45);
    tree2.erase(46);

    tree2.erase(51);
    tree2.erase(52);
    tree2.erase(53);
    tree2.erase(54);
    tree2.erase(55);
    tree2.erase(56);
    //printf("\033[2J");  // 清屏
    y += tree2.print(y+1, false);

    //gotoxy(0, 0); printf("    a\n");
    //gotoxy(0, 1); printf("  b\n");
    //gotoxy(0, 2); printf("c\n");
    //gotoxy(5, 1); printf("h\n");      ⬎⬏⬐⬑↵↓↔←→↑
    //gotoxy(6, 1); printf("  d\n");    ---⬎⬏⬐⬑↵↓↔←→↑

    //gotoxy(5, 2); printf("    e\n");

    //gotoxy(0, y);
    printf("\n");
}
inline void test2_data_1_tree4()
{
    wjg::tree_simple_avl tree2;
    int y = 0;

    for (int i = 0; i < 127; i++)
    {
        tree2.insert(i);
    }

    y = tree2.print(y+1);

    for (int i = 0; i < 90; i++)
    {
        tree2.erase(i);
    }

    y += tree2.print(y+1,false);

    printf("\n");
}
inline void test2_data_1_tree5()
{
    wjg::tree_simple_avl tree2;
    int y = 0;

    for (int i = 0; i < 31; i++)
    {
        tree2.insert(i);
    }

    y = tree2.print(y+1, false);

    tree2.preoder();
    tree2.midoder();
    tree2.postoder();
    y += 3 * 3;

    for (int i = 5; i < 111; i++)
    {
        tree2.erase(i);
    }

    y += tree2.print(y+1, false);

    tree2.preoder();
    tree2.midoder();
    tree2.postoder();
    y += 3 * 3;

    printf("\n");
}
inline void test2_data_1_tree6()
{
    wjg::tree_simple_avl tree2;
    int y = 1;
    for (int i = 0; i < 31; i++) tree2.insert(i);y += tree2.print(y);
    tree2.insert(33);y += tree2.print(y,false);
    tree2.insert(32);y += tree2.print(y,false);
    for (int i = 0; i < 55; i++) tree2.erase(i);//y += tree2.print(y,false);
    // for (int i = 201; i < 222; i++) tree2.insert(i);y += tree2.print(y,false);
    // for (int i = 333; i < 355; i++) tree2.insert(i);y += tree2.print(y,false);
    printf("\n");
}

#endif