#pragma once
#ifndef BTREE_H
#define BTREE_H
#include<stack>
using namespace std;
//树的支点
typedef struct node//家谱中个人信息的载体
{
	char data;
	bool isLchild;
	int level;
	struct node* lchild;
	struct node* rchild;
}Node,*BTNode;//struct node -> Node/*BTNode


class BTree
{
private:
	BTNode root;
public:
	BTree(const char* str);
	~BTree();
	bool isEmpty();
	BTNode getRoot();
	void PostOrderRe(BTNode b);
	void PreOrderRe(BTNode b);
	void PreOrderNotRe();
	bool isAncestor(BTNode b, char me);
	BTNode FindMe(char me);
	BTNode FindFather(BTNode me);
	void FindAllAncestor(char Object);
	void ShowAncestor(BTNode ancestor);
	void DestroyBTree(BTNode b);
	bool banish(char b);//逐出家谱
};


#endif