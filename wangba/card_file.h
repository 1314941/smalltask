#pragma once
#ifndef CARD_FILE_H
#define CARD_FILE_H

int saveCard(Card* acard);                                //������Ϣ���浽����Ϣ�ļ���
Card* readCard();                                //��ȡ����Ϣ�ļ�����Ϣ
Card praseCard(char* bcup);                               //�����ļ��ڵ��ַ���
int updateCard(Card* acard, int index);                   //�����ļ��ڵĿ���Ϣ
int getCardCount();                                         //��ȡ���ļ��ڵĿ���Ϣ����


#endif