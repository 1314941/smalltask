#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include"model.h"
#include"global.h"
#include"tool.h"
#include"billing_file.h"
#include"billing_sevice.h"
lpBillingNode head = NULL;


void releaseBillingList()                                       //�ͷżƷ���Ϣ����
{
	lpBillingNode p1 = head;
	if (head == NULL) {
		return;
	}
	if (p1->next == NULL) {
		free(p1);
		return;
	}
	lpBillingNode p2 = p1->next;
	while (p2->next != NULL) {
		free(p1);
		p1 = p2;
		p2 = p2->next;
	}

	free(p1);
	free(p2);

}




void initBillinglist()
{
	if (head != NULL) {
		releaseBillingList();
	}
	head = (lpBillingNode)malloc(sizeof(BillingNode));
	head->next = NULL;
}




int getBilling()                                                //��ʼ���Ʒ���Ϣ����
{
	int k = 0;
	int i;
	Billing* pb = NULL;
	FILE* fp = NULL;
	initBillinglist();
	pb = readBilling();
	if (pb == NULL) {
		return FALSE;
	}
	k = getBillingCount();
	lpBillingNode node = head;
	lpBillingNode pnode = NULL;
	for (i = 0; i < k; i++) {
		pnode = (lpBillingNode)malloc(sizeof(BillingNode));
		if (pnode == NULL) {
			free(pb);
			return FALSE;
		}
		pnode->data = pb[i];
		pnode->next = NULL;
		node->next = pnode;
		node = node->next;
	}

	return TURE;
}


int addBilling(const char* fcardname)
{
	Billing* pb = NULL;
	pb = (Billing*)malloc(sizeof(Billing));
	strcpy(pb->aCardName, fcardname);
	pb->tStart = time(NULL);
	pb->nDel = 0;
	pb->nstatus = 0;
	pb->fAmount = 0;
	pb->tEnd = 0;
	if (saveBilling(pb) == FALSE) {
		return FALSE;
	}

	return TURE;
}





int queryBilling(const char* pName,Billing* pb ,int* pIndex)                       //��ѯ�Ʒ���Ϣ����
{
	if (getBilling() == FALSE) {
		return FALSE;
	}
	lpBillingNode p = head->next;
	while (p != NULL) {
		if (strcmp(p->data.aCardName, pName) == 0) {
			pb = &p->data;
			return TURE;
		}
		p = p->next;
		(*pIndex)++;
	}

	return TURE;

}



void showinfomation(const char* name)                               //�ݿ�������Ʒ���Ϣ
{
	int ahead = 0;
	if (getBilling() == FALSE) {
		printf("�Ҳ����ÿ���������Ϣ!\n");
		return;
	}
	char startTime[20] = { '\0' };
	char endTime[20] = { '\0' };
	lpBillingNode p = head->next;
	printf("����״̬\t���ѽ��\t�ϻ�ʱ��\t\t�»�ʱ��\t\tɾ����־\n");
	while (p != NULL) {
		if (strcmp(p->data.aCardName, name) == 0) {
			ahead = 1;
			timeToString(p->data.tStart, startTime);
			timeToString(p->data.tEnd, endTime);
			printf("%d\t\t%.2f\t\t%s\t%s\t%d\n", p->data.nstatus, p->data.fAmount,startTime, endTime, p->data.nDel);
		}
		p = p->next;
	}
	if (ahead == 0) {
		printf("�Ҳ����ÿ���������Ϣ!\n");
	}
}

