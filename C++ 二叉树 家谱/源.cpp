#include<iostream>
#include"BTree.h"
using namespace std;


int main(void)
{
	int choose;
	char housemenu[100];
	char me;
	cout << "请以括号表示法输入二义树结构:";
	cin >> housemenu;
	BTree tree(housemenu);
	BTNode r = tree.getRoot();
	cout << "后序遍历递归算法输出:";
	tree.PostOrderRe(r);
	cout << endl<<"前序遍历递归算法输出:";
	tree.PreOrderNotRe();
	cout <<endl<< "请输入指定人物代号，以查询其所有长辈:";
	cin >> me;
	cout << me << "的所有长辈为:";
	tree.FindAllAncestor(me);
	cout << endl << "请输入指定人物代号，以查询其所有同辈:";
	cin >> me;
	BTNode me_BTnode = tree.FindMe(me);
	if (me_BTnode == NULL) {
		cout << "没有此人" << endl;
	}
	else {
		cout << me << "的所有同辈为:";
		tree.ShowAncestor(me_BTnode);
	}
	cout <<endl<< "是否需要进行逐出操作(1-是/0-否):";
	cin >> choose;
	if (choose == 0) {
		return 0;
	}
	cout<< "请输入将被逐出家族的支系的族长:";
	cin >> me;
	me_BTnode = tree.FindMe(me);
	if (me_BTnode == NULL) {
		cout << "没有此人" << endl;
	}
	else {
		cout << "该支系家谱为:";
		tree.PreOrderRe(me_BTnode);
		cout <<endl<< "是否要逐出此支系(1-是/0-否):";
		cin >> choose;
		if (choose == 1) {
			cout << "是否真的要逐出此支系(1-是/0-否):";
			cin >> choose;
			if (choose == 1) {
				if (tree.banish(me)) {
					cout << "逐出后新家谱为：";
					tree.PostOrderRe(r);
				}
				else {
					cout << "逐出失败";
				}
			}
		}
	}


	return 0;
}
