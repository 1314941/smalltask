#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"global.h"
#include"model.h"
#include"card_file.h"
#include"card_sevice.h"
#include"tool.h"
lpCardNode cardhead = NULL;



void releaseCardList()                                          //释放卡信息链表
{
	lpCardNode p1 = cardhead;
	if (cardhead == NULL) {
		return;
	}
	if (p1->next == NULL) {
		free(p1);
		return;
	}
	lpCardNode p2 = p1->next;
	while (p2->next != NULL) {
		free(p1);
		p1 = p2;
		p2 = p2->next;
	}
	free(p1);
	free(p2);

}


int getCard()                                                               //初始化卡信息链表
{
	Card* fcard = NULL;
	lpCardNode node = NULL;
	lpCardNode p = NULL;
	int k = 0, i;
	if (cardhead != NULL) {
		releaseCardList();
	}
	cardhead = (lpCardNode)malloc(sizeof(CardNode));
	cardhead->next = NULL;
	k = getCardCount();
	fcard = readCard();
	if (fcard == NULL) {
		return FALSE;
	}
	for (i = 0, node = cardhead; i < k; i++) {
		p = (lpCardNode)malloc(sizeof(CardNode));
		if (p == NULL) {
			free(fcard);
			fcard = NULL;
			return FALSE;
		}
		p->data = fcard[i];
		node->next = p;
		node = p;
		node->next = NULL;
	}
	free(fcard);
	fcard = NULL;
	return TURE;

}


int isExist(const char* fcardname)                      //检查卡号是否重复
{
	if (getCard() == FALSE) {
		return FALSE;
	}
	lpCardNode p = cardhead->next;
	while (p != NULL) {
		if (strcmp(p->data.aName, fcardname) == 0) {
			return TURE;
		}
		p = p->next;
	}

	return FALSE;

}


void showCard(lpCardNode p)                                     //查询卡时输出卡信息
{
	char lasttime[20] = { '\0' };
	timeToString(p->data.tLast, lasttime);
	printf("%s\t%d\t%.1lf\t%.1lf\t\t%d\t\t%s\n", p->data.aName,
		p->data.nStatus, p->data.fBalance, p->data.fTotalUse, p->data.nUseCount, lasttime);

}



Card* checkCard(const char* fcardname, const char* fpassword, int* index)                       //从卡信息链表中寻找指定的卡信息
{
	getCard();
	lpCardNode p = cardhead->next;
	while (p != NULL) {
		if (strcmp(p->data.aName, fcardname) == 0 && strcmp(p->data.aPwd, fpassword) == 0) {
			return &p->data;
		}
		(*index)++;
		p = p->next;
	}
	return NULL;
}





void queryCard()                                                                  //精确查询
{
	char fcardname[18] = { '\0' };
	printf("请输入查询的卡号:");
	scanf("%s", fcardname);
	lpCardNode node = NULL;
	if (getCard() != TURE) {
		printf("initcardlist!\n");
		return;
	}
	node = cardhead->next;
	printf("----------查询信息如下----------\n");
	while (node != NULL) {
		if (strcmp(node->data.aName, fcardname) == 0) {
			printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
			showCard(node);
			return;
		}
		node = node->next;
	}
	printf("没有该卡的信息!\n");
}



void queryCards()                                                         //模糊查询
{
	int ahead = 0;
	char fcardname[18] = { '\0' };
	printf("请输入查询的关键词:");
	scanf("%s", fcardname);
	lpCardNode node = NULL;
	if (getCard() != TURE) {
		return;
	}
	node = cardhead->next;
	printf("----------查询信息如下----------\n");
	while (node != NULL) {
		if (strstr(node->data.aName, fcardname) != NULL) {
			if (ahead == 0) {
				printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
			}
			showCard(node);
			ahead = 1;
		}
		node = node->next;
	}
	if (ahead == 0) {
		printf("没有该卡信息!\n");
	}
}






float TotalUse()
{
	getCard();
	float sum = 0;
	lpCardNode p = cardhead->next;
	while (p != NULL) {
		sum += p->data.fTotalUse;
		p = p->next;
	}
	
	return sum;
}



float showProfit()
{
	if (getCard() == FALSE) {
		return -1;
	}
	float profit = 0;
	lpCardNode p = cardhead->next;
	while (p != NULL) {
		profit += p->data.fTotalUse - p->data.fBalance;
		p = p->next;
	}

	return profit;
}



void showallCards()                                //输出文件内所有卡信息
{
	if (getCard() == FALSE) {
		printf("找不到卡信息!\n");
	}
	printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
	lpCardNode p = cardhead->next;
	while (p->next != NULL) {
		showCard(p);
		p = p->next;
	}
	showCard(p);

}