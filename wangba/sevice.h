#pragma once
#ifndef SEVICE_H
#define SEVICE_H

int addCardIofo(Card acard);                                                                             //��ӿ�
void queryCardIofo(int choice);                                                                          //��ѯ��
int doLogon(const char* fcardname, const char* fpassword, Logonlofo* plofo);                             //�ϻ�
int doSettle(const char* fcardname, const char* fpassword, Settlelofo* plofo);                          //�»�
int doAddMoney(const char* fcardname, const char* fpassword, Moneylofo* p);                             //��ֵ     
int doRefundMoney(const char* fcardname, const char* fpassword, Moneylofo* p);                         //�˷�
int annulCard(Card* acard);                                                                           //ע����
void count();                                                                                         //��ѯͳ��
float getAmount(time_t tStart);                                                                       //�������
void releaseList();                                                                                  //�ͷ�����


#endif SEVICE_H