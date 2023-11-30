#include<iostream>
#include"SqQueue.h"
#include<string>
using namespace std;
void menu()
{
	cout << endl << "1.排队" << endl;
	cout << "2.就诊" << endl;
	cout << "3.排队人数" << endl;
	cout << "0.退出" << endl;
}

int main(void)
{
	int num;
	SqQueue<string>* p = new SqQueue<string>;
	bool f = true;
	char choice;
	Hospital hp;
	cout << "循环" << endl;
	cout << "-----医院排队系统-----";
	do {
		menu();
		cout << "请输入你的选择:";
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
			cout << "排队人数为:" << num << endl;
			break;
		case '0':
			f = false;
			break;
		default:
			cout << "输入错误" << endl;
		}
	} while (f == true);
	cout << "-----成功退出系统-----" << endl;

	return 0;
}

