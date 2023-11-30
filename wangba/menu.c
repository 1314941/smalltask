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



void outputMenu()                              //输出菜单
{
	printf("----------菜单----------\n");
	printf("1.添加卡\n2.查询卡\n3.上机\n4.下机\n5.充值\n6.退费\n7.查询统计\n8.注销卡\n0.退出\n");
	printf("请选择菜单项序号(0~8):");
}

void add()                                    //添加卡
{
	Card* acard;
	float money = 0;
	int namesize = 0;
	int pwdsize = 0;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	printf("-----添加卡-----\n");
	printf("请输入卡号<长度为1~18>:");
	scanf("%s", fcardname);
	if (isExist(fcardname) == TURE) {
		printf("此卡已存在！\n添加失败!\n\n");
		return;
	}
	printf("请输入密码<长度为1~8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("输入的卡号或密码长度超出规定长度!\n\n");
		return;
	}
	printf("请输入开卡金额<RMB>:");
	while (scanf("%f", &money) != 1) {
		printf("你输入的金额有误!\n请重新输入:");
		while (getchar() != '\n');
	}
	acard = (Card*)malloc(sizeof(Card));
	strcpy(acard->aName, fcardname);
	strcpy(acard->aPwd, fpassword);
	acard->fBalance = money;
	addCardIofo(*acard);
	printf("\n");
}



void query()                               //查询卡
{
	int choice = -1;

	printf("----------查询卡----------\n");
	printf("1.精确查询 \n2.模糊查询\n");
	printf("请输入选择（1或2）:");
	scanf("%d", &choice);

	queryCardIofo(choice);
	printf("\n");

}


void logon()                            //上机
{
	int result = -1;
	int namesize = 0;
	int pwdsize = 0;
	Logonlofo* plofo = NULL;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	char shangjitime[20] = { '\0' };                    //上机时间
	printf("----------上机----------\n");
	printf("请输入上机卡号<长度为1~18>:");
	scanf("%s", fcardname);
	printf("请输入上机密码<长度为1~8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("输入的卡号或密码超出规定长度!\n");
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
		printf("-----上机信息如下-----\n");
		printf("卡号\t余额\t上机时间\n");
		timeToString(plofo->tLogon, shangjitime);
		printf("%s\t%.2f\t%s\n", plofo->aCardName, plofo->fBalance, shangjitime);
		break;
	case FALSE:
		printf("上机失败!\n");
		break;
	case UNUSE:
		printf("该卡正在使用或已注销!\n");
		break;
	case ENOUGHMONEY:
		printf("余额不足!\n");
		break;
	default:
		break;
	}
	printf("\n");
}



void settle()                         //下机
{
	Settlelofo* plofo = NULL;
	int result = -1;
	int namesize = 0;
	int pwdsize = 0;
	char shangjitime[20] = { '\0' };
	char xiajitime[20] = { '\0' };
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	printf("-----下机-----\n");
	printf("请输入下机卡号<长度为1`18>:");
	scanf("%s", fcardname);
	printf("请输入下机密码<长度为1`8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("输入的卡号或密码超出规定长度!\n\n");
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
		printf("下机失败！\n");
	}
	else {
		printf("-----下机信息如下-----\n");
		printf("卡号\t消费\t余额\t上机时间\t\t下机时间\n");
		timeToString(plofo->tStart, shangjitime);
		timeToString(plofo->tEnd, xiajitime);
		printf("%s\t%.2f\t%.2f\t%s\t%s\n", plofo->aCardName, plofo->fAmount, plofo->fBalance, shangjitime, xiajitime);
	}
	printf("\n");

}



void addMoney()                             //充值
{
	Moneylofo* pMoneylofo;
	float money = 0;
	int result = -1;
	int namesize = 0;
	int pwdsize = 0;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	printf("-----充值-----\n");
	printf("请输入充值卡号<长度为1~18>:");
	scanf("%s", fcardname);
	printf("请输入充值密码<长度为1~8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("输入的卡号或密码长度超出规定长度!\n\n");
		return;
	}
	printf("请输入充值金额<RMB>:");
	scanf("%f", &money);
	pMoneylofo = (Moneylofo*)malloc(sizeof(Moneylofo));
	strcpy(pMoneylofo->aCardname, fcardname);
	pMoneylofo->tMoney = money;
	result = doAddMoney(fcardname, fpassword, pMoneylofo);
	printf("-----充值信息如下-----\n");
	if (result == TURE) {
		printf("卡号\t充值金额\t余额\n");
		printf("%s\t%.2f\t\t%.2f\n\n", pMoneylofo->aCardname, pMoneylofo->tMoney, pMoneylofo->fBalance);

	}
	else {
		printf("充值失败\n");
	}
	printf("\n");
}


void refundMoney()                            //退费
{
	Moneylofo* pMoneylofo;
	float money = 0;
	int result = -1;
	int namesize = 0;
	int pwdsize = 0;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	printf("-----退费-----\n");
	printf("请输入退费卡号<长度为1~18>:");
	scanf("%s", fcardname);
	printf("请输入退费密码<1~8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("输入的卡号或密码超出规定长度!\n\n");
		return;
	}
	pMoneylofo = (Moneylofo*)malloc(sizeof(Moneylofo));
	strcpy(pMoneylofo->aCardname, fcardname);
	result = doRefundMoney(fcardname, fpassword, pMoneylofo);
	printf("-----退费信息如下-----\n");
	if (result == TURE) {
		printf("卡号\t退费金额\t余额\n");
		printf("%s\t%.2f\t\t%.2f\n\n", pMoneylofo->aCardname, pMoneylofo->tMoney, pMoneylofo->fBalance);
	}
	else {
		printf("退费失败!\n");
	}
	printf("\n");
}




void count()                                                //查询统计
{
	float profit = 0;
	int cardcount = 0;
	float sum = 0;
	char fcardname[50] = { '\0' };
	int choice = -1;
	printf("-----查询统计-----\n");
	printf("1.所有卡信息\n2.总消费金额\n3.查询卡消费信息\n4.总卡数\n5.营业额\n");
	printf("请输入选择<1`5>:");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		showallCards();
		break;
	case 2:
		sum = TotalUse();
		printf("总消费金额为:%.2f\n", sum);
		break;
	case 3:
		printf("请输入查询卡号<长度为1~18>:");
		scanf("%s", fcardname);
		showinfomation(fcardname);
		break;
	case 4:
		cardcount = getCardCount();
		printf("总卡数:%d\n", cardcount);
		break;
	case 5:
		profit = showProfit();
		printf("营业额:%.2f\n", profit);
		break;
	default:
		printf("输入的序号错误!\n");
		break;
	}
	printf("\n");
}






void annul()                          //注销卡
{
	int result = -1;
	Card* acard = NULL;
	int namesize = 0;
	int pwdsize = 0;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	printf("----------注销卡----------\n");
	printf("请输入注销卡号<长度为1~18>:");
	scanf("%s", fcardname);
	printf("请输入密码<长度为1~8>:");
	scanf("%s", fpassword);
	namesize = strlen(fcardname);
	pwdsize = strlen(fpassword);
	if (namesize > 18 || pwdsize > 8) {
		printf("输入的卡号或密码超出规定长度！\n\n");
		return;
	}
	acard = (Card*)malloc(sizeof(Card));
	strcpy(acard->aName, fcardname);
	strcpy(acard->aPwd, fpassword);
	result = annulCard(acard);
	printf("-----注销信息如下-----\n");
	if (result == TURE) {
		printf("卡号\t退款余额\n");
		printf("%s\t%.2f\n\n", acard->aName, acard->fBalance);
	}
	else {
		printf("注销卡失败!\n");
	}
	printf("\n");

}





void exitApp()
{
	printf("----------退出----------\n\n");
	releaseList();
	printf("请按任意键继续...");
	getchar();

}


