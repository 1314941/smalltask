#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>
#include"tool.h"


void timeToString(time_t atime, char* ftime)                        //��time_t����ת��Ϊ"��-��-�� ʱ����"����   
{
	struct tm* ttime = NULL;

	ttime = localtime(&atime);
	strftime(ftime, 20, "%Y-%m-%d %H:%M", ttime);
}


time_t stringToTime(char* ftime)                               //��"��-��-�� ʱ-��"�ַ���ת��Ϊtime_t����
{
	struct tm ttime;
	time_t time1;

	sscanf(ftime, "%d-%d-%d %d:%d", &ttime.tm_year, &ttime.tm_mon, &ttime.tm_mday,
		&ttime.tm_hour, &ttime.tm_min);

	ttime.tm_year -= 1900;
	ttime.tm_mon -= 1;
	ttime.tm_sec = 0;
	ttime.tm_isdst -= -1;

	time1 = mktime(&ttime);

	return time1;
}
