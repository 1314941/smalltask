#pragma once
#ifndef BILLING_FILE_H
#define BILLING_FILE_H

void releaseBillingList();                                      //释放计费信息链表
void initBillinglist();                                      //初始化计费信息链表
int getBilling();                                      //从文件内读取计费信息到链表
int addBilling(const char* fcardname);                  //添加计费信息到文件
int queryBilling(const char* name,Billing* pb, int* pIndex);            //在计费信息链表内查询计费信息
void showinfomation(const char* name);              //输出计费信息

#endif