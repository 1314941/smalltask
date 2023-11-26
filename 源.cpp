#include<iostream>
#include"BTree.h"
using namespace std;


int main(void)
{
	int choose;
	char housemenu[100];
	char me;
	cout << "�������ű�ʾ������������ṹ:";
	cin >> housemenu;
	BTree tree(housemenu);
	BTNode r = tree.getRoot();
	cout << "��������ݹ��㷨���:";
	tree.PostOrderRe(r);
	cout << endl<<"ǰ������ݹ��㷨���:";
	tree.PreOrderNotRe();
	cout <<endl<< "������ָ��������ţ��Բ�ѯ�����г���:";
	cin >> me;
	cout << me << "�����г���Ϊ:";
	tree.FindAllAncestor(me);
	cout << endl << "������ָ��������ţ��Բ�ѯ������ͬ��:";
	cin >> me;
	BTNode me_BTnode = tree.FindMe(me);
	if (me_BTnode == NULL) {
		cout << "û�д���" << endl;
	}
	else {
		cout << me << "������ͬ��Ϊ:";
		tree.ShowAncestor(me_BTnode);
	}
	cout <<endl<< "�Ƿ���Ҫ�����������(1-��/0-��):";
	cin >> choose;
	if (choose == 0) {
		return 0;
	}
	cout<< "�����뽫����������֧ϵ���峤:";
	cin >> me;
	me_BTnode = tree.FindMe(me);
	if (me_BTnode == NULL) {
		cout << "û�д���" << endl;
	}
	else {
		cout << "��֧ϵ����Ϊ:";
		tree.PreOrderRe(me_BTnode);
		cout <<endl<< "�Ƿ�Ҫ�����֧ϵ(1-��/0-��):";
		cin >> choose;
		if (choose == 1) {
			cout << "�Ƿ����Ҫ�����֧ϵ(1-��/0-��):";
			cin >> choose;
			if (choose == 1) {
				if (tree.banish(me)) {
					cout << "������¼���Ϊ��";
					tree.PostOrderRe(r);
				}
				else {
					cout << "���ʧ��";
				}
			}
		}
	}


	return 0;
}