#pragma once

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>


//����ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//���ó���
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define SUCCESS 1
#define UNSUCCESS -1

//�������Ͷ���
typedef int Status;

// ����������
typedef int TElemType;

// �������ṹ��
typedef struct BiTNode {
	TElemType data;
	struct BiTNode* lchild, * rchild;
} BiTBode, * BiTree;

// ������Ҫ�Ľӿ�
// ����������Ϊ��������������������������
Status BreakBiTree(BiTree& T, BiTree& L, BiTree& R);
// ��ȡ�������
int BiTreeDepth(BiTree T);


#include <Windows.h>

//�ı���λ��
void gotoxy(int x, int y);


/*
* �ݹ��ӡ��ӡ������
* T		���ڴ�ӡ����
* depth	Ŀǰ�ڴ�ӡ���ĵڼ���
* right	�������Ƿ�Ϊ������
* tap	Ŀǰ������Ҫ�����ƫ������
*/
Status Traverse_R(BiTree T, int depth, int right, int tap);

// ��ӡ���νӿ�
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
		int print(int y = 0);
		node_simple* minValueNode(node_simple* root);
		void preoder(node_simple* node);
		void preoder();
		void midoder(node_simple* node);
		void midoder();
		void postoder(node_simple* node);
		void postoder();


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
