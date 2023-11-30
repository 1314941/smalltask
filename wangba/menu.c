#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include"model.h"
#include"global.h"
#include"tool.h"
#include"menu.h"
#include"sevice.h"
#include"billing_file.h"
#include"billing_sevice.h"
#include"card_file.h"
#include"card_sevice.h"



void outputMenu()                              //����˵�
{
	printf("----------�˵�----------\n");
	printf("1.��ӿ�\n2.��ѯ��\n3.�ϻ�\n4.�»�\n5.��ֵ\n6.�˷�\n7.��ѯͳ��\n8.ע����\n0.�˳�\n");
	printf("��ѡ��˵������(0~8):");
}

void add()                                    //��ӿ�
{
	Card* acard;
	float money = 0;
	int namesize = 0;
	int pwdsize = 0;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	printf("-----��ӿ�-----\n");
	printf("�����뿨��<����Ϊ1~18>:");
	scanf("%s", fcardname);
	if (isExist(fcardname) == TURE) {
		printf("�˿��Ѵ��ڣ�\n���ʧ��!\n\n");
		return;
	}
	printf("����������<����Ϊ1~8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("����Ŀ��Ż����볤�ȳ����涨����!\n\n");
		return;
	}
	printf("�����뿪�����<RMB>:");
	while (scanf("%f", &money) != 1) {
		printf("������Ľ������!\n����������:");
		while (getchar() != '\n');
	}
	acard = (Card*)malloc(sizeof(Card));
	strcpy(acard->aName, fcardname);
	strcpy(acard->aPwd, fpassword);
	acard->fBalance = money;
	addCardIofo(*acard);
	printf("\n");
}



void query()                               //��ѯ��
{
	int choice = -1;

	printf("----------��ѯ��----------\n");
	printf("1.��ȷ��ѯ \n2.ģ����ѯ\n");
	printf("������ѡ��1��2��:");
	scanf("%d", &choice);

	queryCardIofo(choice);
	printf("\n");

}


void logon()                            //�ϻ�
{
	int result = -1;
	int namesize = 0;
	int pwdsize = 0;
	Logonlofo* plofo = NULL;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	char shangjitime[20] = { '\0' };                    //�ϻ�ʱ��
	printf("----------�ϻ�----------\n");
	printf("�������ϻ�����<����Ϊ1~18>:");
	scanf("%s", fcardname);
	printf("�������ϻ�����<����Ϊ1~8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("����Ŀ��Ż����볬���涨����!\n");
	}
	plofo = (Logonlofo*)malloc(sizeof(Logonlofo));
	if (plofo == NULL) {
		return;
	}
	strcpy(plofo->aCardName, fcardname);
	plofo->tLogon = time(NULL);
	result = doLogon(fcardname, fpassword, plofo);
	switch (result) {
	case TURE:
		printf("-----�ϻ���Ϣ����-----\n");
		printf("����\t���\t�ϻ�ʱ��\n");
		timeToString(plofo->tLogon, shangjitime);
		printf("%s\t%.2f\t%s\n", plofo->aCardName, plofo->fBalance, shangjitime);
		break;
	case FALSE:
		printf("�ϻ�ʧ��!\n");
		break;
	case UNUSE:
		printf("�ÿ�����ʹ�û���ע��!\n");
		break;
	case ENOUGHMONEY:
		printf("����!\n");
		break;
	default:
		break;
	}
	printf("\n");
}



void settle()                         //�»�
{
	Settlelofo* plofo = NULL;
	int result = -1;
	int namesize = 0;
	int pwdsize = 0;
	char shangjitime[20] = { '\0' };
	char xiajitime[20] = { '\0' };
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	printf("-----�»�-----\n");
	printf("�������»�����<����Ϊ1`18>:");
	scanf("%s", fcardname);
	printf("�������»�����<����Ϊ1`8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("����Ŀ��Ż����볬���涨����!\n\n");
		return;
	}
	plofo = (Settlelofo*)malloc(sizeof(Settlelofo));
	if (plofo == NULL) {
		return;
	}
	strcpy(plofo->aCardName, fcardname);
	plofo->tStart = time(NULL);
	result = doSettle(fcardname, fpassword, plofo);
	if (result == FALSE) {
		printf("�»�ʧ�ܣ�\n");
	}
	else {
		printf("-----�»���Ϣ����-----\n");
		printf("����\t����\t���\t�ϻ�ʱ��\t\t�»�ʱ��\n");
		timeToString(plofo->tStart, shangjitime);
		timeToString(plofo->tEnd, xiajitime);
		printf("%s\t%.2f\t%.2f\t%s\t%s\n", plofo->aCardName, plofo->fAmount, plofo->fBalance, shangjitime, xiajitime);
	}
	printf("\n");

}



void addMoney()                             //��ֵ
{
	Moneylofo* pMoneylofo;
	float money = 0;
	int result = -1;
	int namesize = 0;
	int pwdsize = 0;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	printf("-----��ֵ-----\n");
	printf("�������ֵ����<����Ϊ1~18>:");
	scanf("%s", fcardname);
	printf("�������ֵ����<����Ϊ1~8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("����Ŀ��Ż����볤�ȳ����涨����!\n\n");
		return;
	}
	printf("�������ֵ���<RMB>:");
	scanf("%f", &money);
	pMoneylofo = (Moneylofo*)malloc(sizeof(Moneylofo));
	strcpy(pMoneylofo->aCardname, fcardname);
	pMoneylofo->tMoney = money;
	result = doAddMoney(fcardname, fpassword, pMoneylofo);
	printf("-----��ֵ��Ϣ����-----\n");
	if (result == TURE) {
		printf("����\t��ֵ���\t���\n");
		printf("%s\t%.2f\t\t%.2f\n\n", pMoneylofo->aCardname, pMoneylofo->tMoney, pMoneylofo->fBalance);

	}
	else {
		printf("��ֵʧ��\n");
	}
	printf("\n");
}


void refundMoney()                            //�˷�
{
	Moneylofo* pMoneylofo;
	float money = 0;
	int result = -1;
	int namesize = 0;
	int pwdsize = 0;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	printf("-----�˷�-----\n");
	printf("�������˷ѿ���<����Ϊ1~18>:");
	scanf("%s", fcardname);
	printf("�������˷�����<1~8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("����Ŀ��Ż����볬���涨����!\n\n");
		return;
	}
	pMoneylofo = (Moneylofo*)malloc(sizeof(Moneylofo));
	strcpy(pMoneylofo->aCardname, fcardname);
	result = doRefundMoney(fcardname, fpassword, pMoneylofo);
	printf("-----�˷���Ϣ����-----\n");
	if (result == TURE) {
		printf("����\t�˷ѽ��\t���\n");
		printf("%s\t%.2f\t\t%.2f\n\n", pMoneylofo->aCardname, pMoneylofo->tMoney, pMoneylofo->fBalance);
	}
	else {
		printf("�˷�ʧ��!\n");
	}
	printf("\n");
}




void count()                                                //��ѯͳ��
{
	float profit = 0;
	int cardcount = 0;
	float sum = 0;
	char fcardname[50] = { '\0' };
	int choice = -1;
	printf("-----��ѯͳ��-----\n");
	printf("1.���п���Ϣ\n2.�����ѽ��\n3.��ѯ��������Ϣ\n4.�ܿ���\n5.Ӫҵ��\n");
	printf("������ѡ��<1`5>:");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		showallCards();
		break;
	case 2:
		sum = TotalUse();
		printf("�����ѽ��Ϊ:%.2f\n", sum);
		break;
	case 3:
		printf("�������ѯ����<����Ϊ1~18>:");
		scanf("%s", fcardname);
		showinfomation(fcardname);
		break;
	case 4:
		cardcount = getCardCount();
		printf("�ܿ���:%d\n", cardcount);
		break;
	case 5:
		profit = showProfit();
		printf("Ӫҵ��:%.2f\n", profit);
		break;
	default:
		printf("�������Ŵ���!\n");
		break;
	}
	printf("\n");
}






void annul()                          //ע����
{
	int result = -1;
	Card* acard = NULL;
	int namesize = 0;
	int pwdsize = 0;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	printf("----------ע����----------\n");
	printf("������ע������<����Ϊ1~18>:");
	scanf("%s", fcardname);
	printf("����������<����Ϊ1~8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("����Ŀ��Ż����볬���涨���ȣ�\n\n");
		return;
	}
	acard = (Card*)malloc(sizeof(Card));
	strcpy(acard->aName, fcardname);
	strcpy(acard->aPwd, fpassword);
	result = annulCard(acard);
	printf("-----ע����Ϣ����-----\n");
	if (result == TURE) {
		printf("����\t�˿����\n");
		printf("%s\t%.2f\n\n", acard->aName, acard->fBalance);
	}
	else {
		printf("ע����ʧ��!\n");
	}
	printf("\n");

}





void exitApp()
{
	printf("----------�˳�----------\n\n");
	releaseList();
	printf("�밴���������...");
	getchar();

}


