#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include"model.h"
#include"global.h"
#include"tool.h"
#include"billing_sevice.h"
#include"billing_file.h"


int getBillingCount()                                              //获取文件内计费信息的个数
{
	FILE* fp = NULL;
	Billing* temp = NULL;
	int k = 0;
	fp = fopen(BILLING_PATH, "rb");
	if (fp == NULL) {
		return 0;
	}
	temp = (Billing*)malloc(sizeof(Billing));
	while (!feof(fp)) {                                       //检查文件指针是否到尾端
		if (fread(temp, sizeof(Billing), 1, fp) != 0) {
			k++;
		}
	}
	fclose(fp);
	free(temp);
	return k;
}




int saveBilling(Billing* pb)                                   //将计费信息保存到文件
{
	FILE* fp = NULL;
	fp = fopen(BILLING_PATH, "ab");
	if (fp == NULL) {
		fp = fopen(BILLING_PATH, "wb");
		if (fp == NULL) {
			return FALSE;
		}
	}
	fwrite(pb, sizeof(Billing), 1, fp);
	fclose(fp);
	return TURE;

}




Billing* readBilling()
{
	Billing* pb = NULL;
	FILE* fp = NULL;
	int k = 0;
	k = getBillingCount();
	pb = (Billing*)malloc(sizeof(Billing) * k);
	if (pb == NULL) {
		return NULL;
	}
	fp = fopen(BILLING_PATH, "rb");
	if (fp == NULL) {
		free(pb);
		return NULL;
	}
	if (fread(pb, sizeof(Billing), k, fp) == 0) {
		fclose(fp);
		free(pb);
		return NULL;
	}
	fclose(fp);
	return pb;

}





int updateBilling(Billing* p, int index)                                  //更新文件内的计费信息
{
	FILE* fp = NULL;
	int i = 0;
	int k = 0;
	Billing* bp = NULL;
	bp = readBilling();
	if (bp == NULL) {
		return FALSE;
	}
	k = getBillingCount();
	bp[index] = *p;
	fp = fopen(BILLING_PATH, "wb");
	if (fp == NULL) {
		return FALSE;
	}
	for (i = 0; i < k; i++) {
		fwrite(&bp[i], sizeof(Billing), 1, fp);
	}
	fclose(fp);
	return TURE;
}










