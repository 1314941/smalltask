#include<iostream>
#include"Queue.h"
#include<string>
using namespace std;
void menu()
{
	cout <<endl<< "1.�Ŷ�" << endl;
	cout << "2.����" << endl;
	cout << "3.�Ŷ�����" << endl;
	cout << "0.�˳�" << endl;
}

int main(void)
{
	int num;
	LinkQueue<string>* p=new LinkQueue<string>;
	bool f = true;
    char choice;
	Hospital hp;
	cout << "-----ҽԺ�Ŷ�ϵͳ-----";
	do {
		menu();
		cout << "���������ѡ��:";
		cin >> choice;
		switch (choice) {
		case '1':
			hp.enQueue(p);
			break;
		case '2':
			hp.visit(p);
			break;
		case '3':
			num=hp.total(p);
			cout << "�Ŷ�����Ϊ:" << num<<endl;
			break;
		case '0':
			f = false;
			break;
		default:
			cout << "�������"<<endl;
		}
	} while (f == true);
	cout << "-----�ɹ��˳�ϵͳ-----"<<endl;
	return 0;
}