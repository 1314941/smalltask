#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "model.h"
#include "menu.h"

// ����˵�
int main(void)
{
	int nSelection = 0; // ����ѡ��ı���
	printf("��ӭ����Ʒѹ���ϵͳ\n\n");
	do
	{ // ѭ������˵�
		outputMenu();
		while (scanf("%d", &nSelection) != 1)
		{
			printf("����Ĳ˵�����Ŵ���!\n");
			while (getchar() != '\n')
				;
		}
		getchar();
		switch (nSelection)
		{ // ��������������˵�
		case 1:
			add(); // ��ӿ�
			break;
		case 2:
			query(); // ��ѯ��
			break;
		case 3:
			logon(); // �ϻ�
			break;
		case 4:
			settle(); // �»�
			break;
		case 5:
			addMoney(); // ��ֵ
			break;
		case 6:
			refundMoney(); // �˷�
			break;
		case 7:
			count(); // ��ѯͳ��
			break;
		case 8:
			annul(); // ע����
			break;
		case 0:
			exitApp(); // �˳�
			break;
		default:
			printf("����Ĳ˵���Ŵ���\n\n");
			break;
		}
	} while (nSelection != 0); // ѡ��Ϊ0ʱѭ��ֹͣ

	return 0;
}