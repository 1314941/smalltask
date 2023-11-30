#pragma once
#ifndef CARD_FILE_H
#define CARD_FILE_H

int saveCard(Card* acard);                                //将卡信息保存到卡信息文件内
Card* readCard();                                //读取卡信息文件的信息
Card praseCard(char* bcup);                               //解析文件内的字符串
int updateCard(Card* acard, int index);                   //更新文件内的卡信息
int getCardCount();                                         //获取卡文件内的卡信息个数


#endif