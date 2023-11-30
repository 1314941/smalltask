#define _CRT_SECURE_NO_WARNINGS   
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdlib.h>
#include"model.h"
#include"tool.h"
#include"global.h"
#include"billing_file.h"
#include"billing_sevice.h"
#include"card_file.h"
#include"card_sevice.h"
#include"sevice.h"



int addCardIofo(Card fcard)                      //添加卡
{
	struct tm* etime = NULL;
	fcard.nStatus = 0;
	fcard.nDel = 0;
	fcard.tStart = fcard.tLast = fcard.tEnd = time(NULL);
	etime = localtime(&fcard.tEnd);
	etime->tm_year++;
	fcard.tEnd = mktime(etime);
	fcard.fTotalUse = fcard.fBalance;
	fcard.nUseCount = 0;
	if (saveCard(&fcard) !=TURE ) {
		printf("添加卡信息失败!\n");
		return FALSE;
	}
	printf("添加卡信息成功！\n");
	return TURE;
}


void queryCardIofo(int choice)                                          //查询卡
{
	if (choice == 1) {                                             //精确查询
		queryCard();
	}
	else if (choice == 2) {
		queryCards();                                            //模糊查询
	}
	else {
		printf("输入错误!\n");
	}
}



int doLogon(const char* fcardname, const char* fpassword, Logonlofo* plofo)                        //上机
{
	Card* acard = NULL;
	int index = 0;
	acard = checkCard(fcardname, fpassword, &index);
	if (acard == NULL) {
		return FALSE;
	}
	if (acard->nStatus != 0) {
		return UNUSE;
	}
	if (acard->fBalance <= 0) {
		return ENOUGHMONEY;
	}
	acard->nStatus = 1;
	acard->tLast = time(NULL);
	if (updateCard(acard, index) != TURE) {
		printf("更新失败!\n");
		return FALSE;
	}
	plofo->fBalance = acard->fBalance;
	if (addBilling(fcardname) == FALSE) {
		printf("计费信息保存失败!\n");
		return FALSE;
	}
	return TURE;

}



int doSettle(const char* fcardname, const char* fpassword, Settlelofo* plofo)             //下机
{
	Card* acard = NULL;
	int index = 0;
	float amount = 0;
	acard = checkCard(fcardname, fpassword, &index);
	if (acard == NULL) {
		printf("没有该卡信息!\n");
		return FALSE;
	}
	if (acard->nStatus != 1) {
		printf("该卡未上机或已注销!\n");
		return FALSE;
	}
	amount = getAmount(plofo->tStart);
	if (acard->fBalance < amount) {
		printf("余额不足！\n请充值！\n");
		return FALSE;
	}
	acard->fBalance -= amount;
	acard->nUseCount++;
	acard->nStatus = 0;
	time_t temp = acard->tLast;
	acard->tLast = time(NULL);
	if (updateCard(acard, index) != TURE) {
		printf("卡信息保存失败!\n");
	}
	plofo->fBalance = acard->fBalance;
	plofo->tEnd = time(NULL);
	plofo->fAmount = amount;
	Billing pb ;
	int index2 = 0;
	if (queryBilling(fcardname, &pb, &index2) == FALSE) {
		printf("没有该消费信息!\n");
		return FALSE;
	}
	strcpy(pb.aCardName, fcardname);
	pb.tStart = temp;
	pb.nDel = 0;
	pb.nstatus = 0;
	pb.fAmount = amount;
	pb.tEnd = time(NULL);
	if (updateBilling(&pb, index2) == FALSE) {
		printf("更新计费信息失败!\n");
		return FALSE;
	}
	return TURE;

}




int doAddMoney(const char* fcardname, const char* fpassword, Moneylofo* plofo)              //充值
{
	int index = 0;
	Card* acard = NULL;
	acard = checkCard(fcardname, fpassword, &index);
	if (acard == NULL) {
		return FALSE;
	}
	if (acard->nStatus != 0) {
		printf("该卡正在使用或已注销!\n");
		return FALSE;
	}
	acard->fBalance += plofo->tMoney;
	updateCard(acard, index);
	plofo->fBalance = acard->fBalance;
	add_Money(fcardname, plofo->tMoney);

	return TURE;
}


int doRefundMoney(const char* fcardname, const char* fpassword, Moneylofo* plofo)                //退费
{
	Card* acard = NULL;
	int index = 0;
	acard = checkCard(fcardname, fpassword, &index);
	if (acard == NULL) {
		return FALSE;
	}
	if (acard->nStatus == 2 || acard->nStatus == 3) {
		printf("该卡已注销或已失效!\n");
		return FALSE;
	}
	if (acard->fBalance < plofo->tMoney) {
		printf("你的余额不足！\n");
		return FALSE;
	}
	plofo->tMoney = acard->fBalance;
	acard->fBalance = 0;
	plofo->fBalance = 0;
	if (updateCard(acard, index) != TURE) {
		printf("充值信息保存失败");
		return FALSE;
	}
	add_Money(fcardname, plofo->tMoney);

	return TURE;
}



int annulCard(Card* acard)                             //注销卡
{
	int index = 0;
	char fcardname[50] = { '\0' };
	char fpassword[50] = { '\0' };
	strcpy(fcardname, acard->aName);
	strcpy(fpassword, acard->aPwd);
	Card* bcard = NULL;
	bcard = checkCard(fcardname, fpassword, &index);
	if (bcard == NULL) {
		return FALSE;
	}
	if (bcard->nStatus != 0) {
		printf("该卡正在使用或已注销!\n");
		return FALSE;
	}
	acard->fBalance = bcard->fBalance;
	bcard->nStatus = 3;
	bcard->fBalance = 0;
	if (updateCard(bcard, index) != TURE) {
		printf("注销信息保存失败!\n");
		return FALSE;
	}
	return TURE;
}





float getAmount(time_t tStart)                          //计费
{
	float charge;
	time_t tEnd = time(NULL);
	int min;
	min = (tEnd - tStart) / 60;
	charge = min * CHARGES;

	return charge;
}




void releaseList()                         //释放链表
{
	releaseCardList();
	releaseBillingList();

}




