#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"model.h"
#include"global.h"
#include"tool.h"
#include"money_file.h"
#include"money_sevice.h"

int add_Money(const char* fcardname, float money)                   //������˷���Ϣ
{
	Money* p = NULL;
	p = (Money*)malloc(sizeof(Money));
	if (p == NULL) {
		return FALSE;
	}
	strcpy(p->aCardName, fcardname);
	p->Del = 0;
	p->nStatus = 0;
	p->tMoney = money;
	p->tTime = time(NULL);
	if (saveMoney(p) == FALSE) {
		printf("���˷���Ϣʧ�ܣ�\n");
	}

	return TURE;
}