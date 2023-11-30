#pragma once
#ifndef CARD_SEVICE_H
#define CARD_SEVICE_H

void releaseCardList();                                                                    //释放卡信息链表
int getCard();                                                                           //初始化卡信息链表
int isExist(const char* fcardname);                                                          //检查卡号是否重复
void showCard(lpCardNode p);                                                               //查询卡时输出卡信息
Card* checkCard(const char* fcardname, const char* fpassword, int* index);                 //在卡信息链表内查询卡信息
void queryCard();                                                                           //精确查询
void queryCards();                                                                           //模糊查询
float TotalUse();                                                                            //总使用金额
float showProfit();                                                                         //总利润
void showallCards();                                       //输出所有卡信息


#endif