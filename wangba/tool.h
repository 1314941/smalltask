#pragma once
#ifndef TOOL_H
#define TOOL_H

#include<time.h>
void timeToString(time_t ptime, char* Cardtime);                   //��time_t����ת��Ϊ"��-��-�� ʱ����"�ַ���
time_t stringToTime(char* Cardtime);                               //��"��-��-�� ʱ����"�ַ���ת��Ϊtime_t����

#endif