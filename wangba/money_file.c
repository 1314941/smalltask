#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include"model.h"
#include"global.h"
#include"tool.h"
#include"money_file.h"
#include"money_sevice.h"

int saveMoney(const Money* pMoney)                                 // �����˷���Ϣ���浽�ļ�
{
	FILE* fp = NULL;
	fp = fopen(MONEY_PATH, "ab");
	if (fp == NULL) {
		fp = fopen(MONEY_PATH, "w");
		if (fp == NULL) {
			return NULL;
		}
	}
	fwrite(pMoney, sizeof(Money), 1, fp);

	fclose(fp);

	return TURE;
}


