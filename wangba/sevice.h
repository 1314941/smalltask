#pragma once
#ifndef SEVICE_H
#define SEVICE_H

int addCardIofo(Card acard);                                                                             //添加卡
void queryCardIofo(int choice);                                                                          //查询卡
int doLogon(const char* fcardname, const char* fpassword, Logonlofo* plofo);                             //上机
int doSettle(const char* fcardname, const char* fpassword, Settlelofo* plofo);                          //下机
int doAddMoney(const char* fcardname, const char* fpassword, Moneylofo* p);                             //充值     
int doRefundMoney(const char* fcardname, const char* fpassword, Moneylofo* p);                         //退费
int annulCard(Card* acard);                                                                           //注销卡
void count();                                                                                         //查询统计
float getAmount(time_t tStart);                                                                       //计算费用
void releaseList();                                                                                  //释放链表


#endif SEVICE_H