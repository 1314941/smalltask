#pragma once
#ifndef TOOL_H
#define TOOL_H

#include<time.h>
void timeToString(time_t ptime, char* Cardtime);                   //将time_t类型转换为"年-月-日 时：分"字符串
time_t stringToTime(char* Cardtime);                               //将"年-月-日 时：分"字符串转换为time_t类型

#endif