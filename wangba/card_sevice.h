#pragma once
#ifndef CARD_SEVICE_H
#define CARD_SEVICE_H

void releaseCardList();                                                                    //�ͷſ���Ϣ����
int getCard();                                                                           //��ʼ������Ϣ����
int isExist(const char* fcardname);                                                          //��鿨���Ƿ��ظ�
void showCard(lpCardNode p);                                                               //��ѯ��ʱ�������Ϣ
Card* checkCard(const char* fcardname, const char* fpassword, int* index);                 //�ڿ���Ϣ�����ڲ�ѯ����Ϣ
void queryCard();                                                                           //��ȷ��ѯ
void queryCards();                                                                           //ģ����ѯ
float TotalUse();                                                                            //��ʹ�ý��
float showProfit();                                                                         //������
void showallCards();                                       //������п���Ϣ


#endif