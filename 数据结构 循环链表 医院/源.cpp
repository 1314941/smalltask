#include<iostream>
#include"SqQueue.h"
#include<string>
using namespace std;
void menu()
{
	cout << endl << "1.�Ŷ�" << endl;
	cout << "2.����" << endl;
	cout << "3.�Ŷ�����" << endl;
	cout << "0.�˳�" << endl;
}

int main(void)
{
	int num;
	SqQueue<string>* p = new SqQueue<string>;
	bool f = true;
	char choice;
	Hospital hp;
	cout << "ѭ��" << endl;
	cout << "-----ҽԺ�Ŷ�ϵͳ-----";
	do {
		menu();
		cout << "���������ѡ��:";
		cin >> choice;
		switch (choice) {
		case '1':
			hp.enqueue(p);
			break;
		case '2':
			hp.jiuzhen(p);
			break;
		case '3':
			num = hp.total(p);
			cout << "�Ŷ�����Ϊ:" << num << endl;
			break;
		case '0':
			f = false;
			break;
		default:
			cout << "�������" << endl;
		}
	} while (f == true);
	cout << "-----�ɹ��˳�ϵͳ-----" << endl;

	return 0;
}

