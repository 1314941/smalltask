#include<iostream>
#include<stack>
#include"BTree.h"
using namespace std;


BTree::BTree(const char* str)
{
	stack<BTNode> st;
	BTNode p;
	bool flag = true;
	int i = 0;
	while (str[i] != '\0') {
		switch (str[i]) {
		case'(':
			st.push(p);
			flag = true;
			break;
		case')':
			st.pop();
			break;
		case',':
			flag = false;
			break;
		default:;
			p = new Node;
			p->data = str[i];
			p->lchild = NULL;//要记得
			p->rchild = NULL;//要记得
			if (root == NULL) {
				p->isLchild = true;
				p->level = 1;
				root = p;
			}
			else {
				if (!st.empty()) {
					p->level += st.top()->level;
					if (flag) {
						st.top()->lchild = p;
						p->isLchild = true;
					}
					else if (!st.empty()) {
						st.top()->rchild = p;
						p->isLchild = false;
					}
				}
			}
		}
		i++;
	}
}



BTree::~BTree()
{
	if (root == NULL) {
		
	}
	else {
		DestroyBTree(root);
	}
}


bool BTree::isEmpty()
{
	if (root == NULL) {
		return true;
	}
	return false;
}


BTNode BTree::getRoot()
{
	BTNode b = root;
	return b;
}








void BTree::PostOrderRe(BTNode b)
{
	if (b->lchild != NULL || b->rchild != NULL) {
		cout << "(";
		if (b->lchild != NULL) {
			PostOrderRe(b->lchild);
		}
		if (b->rchild != NULL) {
			cout << ",";
			PostOrderRe(b->rchild);
		}
		cout << ")";
	}
	cout << b->data;
	return;
}



void BTree::PreOrderRe(BTNode b)
{
	cout << b->data;
	if (b->lchild != NULL || b->rchild != NULL) {
		cout << "(";
		if (b->lchild != NULL) {
			PreOrderRe(b->lchild);
		}
		if (b->rchild != NULL) {
			cout << ",";
			PreOrderRe(b->rchild);
		}
		cout << ")";
	}
	return;
}









void BTree::PreOrderNotRe()
{
	stack<BTNode> st;
	BTNode p;
	p = root;
	while (!st.empty() || p != NULL) {
		if (p != NULL) {
			cout << p->data;
			st.push(p);
			p = p->lchild;
		}
		else {
			p=st.top();
			st.pop();
			p = p->rchild;
		}
	}
	return;
}


bool BTree::isAncestor(BTNode b, char me)
{
	if (b == NULL) {
		return false;
	}
	else if (b->lchild != NULL && b->lchild->data == me || b->rchild != NULL && b->rchild->data == me) {
		cout << b->data;
		ShowAncestor(b);
		return true;
	}
	else if (isAncestor(b->lchild, me) || isAncestor(b->rchild, me)) {
		cout << b->data;
		ShowAncestor(b);
		return true;
	}
	return false;
}



void BTree::FindAllAncestor(char me)
{
	isAncestor(root, me);
	return;
}




BTNode BTree::FindMe(char me)
{
	stack<BTNode> st;
	BTNode p;
	p = root;
	while (!st.empty() || p != NULL) {
		if (p != NULL) {
			if (p->data == me) {
				return p;
			}
			st.push(p);
			p = p->lchild;
		}
		else {
			p = st.top();
			st.pop();
			p = p->rchild;
		}
	}
	return NULL;
}




BTNode BTree::FindFather(BTNode me)
{
	stack<BTNode> st;
	BTNode p;
	p = root;
	while (!st.empty() || p != NULL) {
		if (p != NULL) {
			if (p->lchild==me||p->rchild==me) {
				return p;
			}
			st.push(p);
			p = p->lchild;
		}
		else {
			p = st.top();
			st.pop();
			p = p->rchild;
		}
	}
	return NULL;
}



void BTree::ShowAncestor(BTNode ancestor)
{
	stack<BTNode> st;
	BTNode p;
	p = root;
	while (!st.empty() || p != NULL) {
		if (p != NULL) {
			if (p->level == ancestor->level&&p!=ancestor) {
				cout << p->data;
			}
			st.push(p);
			p = p->lchild;
		}
		else {
			p = st.top();
			st.pop();
			p = p->rchild;
		}
	}
	return;
}


bool BTree::banish(char me)
{
	BTNode b = FindMe(me);
	BTNode father;
	if (b == NULL) {
		return false;
	}
	else {
		if (b == root) {

		}
		else {
			father = FindFather(b);
			if (father == NULL) {
				cout << "找不到此人父亲"<<endl;
				return false;
			}
			if (b->isLchild) {
				father->lchild = NULL;
			}
			else {
				father->rchild = NULL;
			}
		}
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		delete(b);
	}
	return true;
}




void BTree::DestroyBTree(BTNode b)
{
	if (b == NULL) {
		return;
	}
	else{ 
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		delete(b);
	}
	return;
}