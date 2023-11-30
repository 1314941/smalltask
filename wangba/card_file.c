#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include"model.h"
#include"global.h"
#include"card_file.h"
#include"card_sevice.h"
#include"tool.h"


Card praseCard(char* bcup)                                        //解析文件内字符串
{
	Card fcard;
	char* cup = NULL;
	char* app = NULL;
	char flag[10][20] = { '\0' };
	int count = 0;
	cup = bcup;

	while ((app = strtok(cup, SEPRATIVE)) != NULL) {
		strcpy(flag[count], app);
		cup = NULL;
		count++;
	}
	strcpy(fcard.aName, flag[0]);
	strcpy(fcard.aPwd, flag[1]);
	fcard.nStatus = atoi(flag[2]);                             //atoi() 将字符串转换为int类型
	fcard.tStart = stringToTime(flag[3]);
	fcard.tEnd = stringToTime(flag[4]);
	fcard.fTotalUse = atof(flag[5]);                           //atof()将字符串转换为double类型
	fcard.tLast = stringToTime(flag[6]);
	fcard.nUseCount = atoi(flag[7]);
	fcard.fBalance = atof(flag[8]);
	fcard.nDel = atoi(flag[9]);

	return fcard;
}



Card* readCard()                                       //从文件中读取卡信息
{
	Card* fcard = NULL;
	int i = 0;
	int k;
	FILE* fp;
	char acup[100] = { '\0' };
	fp = fopen(CARD_PATH, "r");
	if (fp == NULL) {
		return NULL;
	}
	k = getCardCount();                                                //获取文件内的卡个数
	fcard = (Card*)malloc(sizeof(Card) * k);
	if (fcard == NULL) {                                             //获取内存失败
		fclose(fp);
		return NULL;
	}
	while (!feof(fp)) {                                              //检测文件是否结束
		memset(acup, 0, 100);
		fgets(acup, 99, fp);
		if (strlen(acup) > 0) {
			fcard[i] = praseCard(acup);
			i++;
		}
	}
	fclose(fp);
	return fcard;

}





int getCardCount()                                              //获取文件内卡的个数
{
	FILE* fp = NULL;
	char acup[100] = { '\0' };
	int k = 0;
	fp = fopen(CARD_PATH, "r");
	if (fp == NULL) {
		return 0;
	}
	while (!feof(fp)) {
		memset(acup, 0, 100);
		fgets(acup, 99, fp);
		if (strlen(acup) > 0) {
			k++;
		}
	}
	fclose(fp);

	return k;
}


int saveCard(Card* d)                                               //将卡信息保存进文件
{
	char sTime[20] = { '\0' };
	char eTime[20] = { '\0' };
	char LastTime[20] = { '\0' };
	FILE* fp = NULL;
	if ((fp = fopen(CARD_PATH, "a")) == NULL) {
		if ((fp = fopen(CARD_PATH, "w")) == NULL) {
			perror("文件打开失败");
			return FALSE;
		}
	}
	timeToString(d->tStart, sTime);
	timeToString(d->tEnd, eTime);
	timeToString(d->tLast, LastTime);
	fprintf(fp, "%s##%s##%d##%s##%s##%.1f##%s##%d##%.1f##%d\n", d->aName, d->aPwd, d->nStatus,
		sTime, eTime, d->fTotalUse, LastTime, d->nUseCount, d->fBalance, d->nDel);
	fclose(fp);                                                        //关闭文件

	return TURE;

}






int updateCard(Card* d, int index)                    //更新卡信息
{
	char stime[20] = { '\0' };
	char etime[20] = { '\0' };
	char ltime[20] = { '\0' };
	int i;
	int k = 0;
	FILE* fp = NULL;
	Card* fcard = NULL;
	fcard = readCard();
	if (fcard == NULL) {
		return FALSE;
	}
	k = getCardCount();
	fcard[index] = *d;
	fp = fopen(CARD_PATH, "w");
	if (fp == NULL) {
		return FALSE;
	}
	for (i = 0; i < k; i++) {
		timeToString(fcard[i].tStart, stime);
		timeToString(fcard[i].tEnd, etime);
		timeToString(fcard[i].tLast, ltime);
		fprintf(fp, "%s##%s##%d##%s##%s##%.1f##%s##%d##%.1f##%d\n", fcard[i].aName, fcard[i].aPwd, fcard[i].nStatus,
			stime, etime, fcard[i].fTotalUse, ltime, fcard[i].nUseCount, fcard[i].fBalance, fcard[i].nDel);
	}
	fclose(fp);
	return TURE;

}













