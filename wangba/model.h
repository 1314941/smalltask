#pragma once
#ifndef MODEL_H
#define MODEL_H

#include<time.h>
//���忨��Ϣ�ṹ��
typedef struct Card  //����Ϣ�ṹ��
{
	char aName[50];  //����
	char aPwd[50];       //����
	int nStatus;     //��״̬��0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ��
	time_t tStart;   //����ʱ��
	time_t tEnd;     //���Ľ�ֹʱ��
	float fTotalUse;   //�ۼƽ��
	time_t tLast;       //���ʹ��ʱ��
	int   nUseCount;   //ʹ�ô���
	float fBalance;    //���
	int nDel;         //ɾ����־ 0-δɾ���� 1-ɾ��
}Card;

typedef struct CardNode             //����Ϣ�ڵ�
{
	Card data;
	struct CardNode* next;
}*lpCardNode, CardNode;



typedef struct Billing          //�Ʒ���Ϣ
{
	char aCardName[50];
	time_t tStart;                //�ϻ�ʱ��
	time_t tEnd;               //�»�ʱ��
	float fAmount;              //���ѽ��
	int nstatus;                 //�ϻ�����״̬
	int nDel;                       //ɾ����־
}Billing;


typedef struct BilllingNode             //�Ʒ���Ϣ�ڵ�
{
	Billing data;
	struct BillingNode* next;
}BillingNode, * lpBillingNode;



typedef struct Logonlofo                 //�ϻ���Ϣ
{
	char aCardName[50];
	time_t tLogon;
	float fBalance;
}Logonlofo;


typedef struct Settlelofo               //�»���Ϣ
{
	char aCardName[50];
	time_t tStart;
	time_t tEnd;
	float fAmount;
	float fBalance;
}Settlelofo;



typedef struct Money               //���˷���Ϣ
{
	char aCardName[50];            //����
	time_t tTime;                  //��ֵ�˷ѵ�ʱ��
	int nStatus;                   //״̬��0��ʾ��ֵ��1��ʾ�˷�
	float tMoney;                //��ֵ�˷ѽ��
	int Del;                      //ɾ����־��0-δɾ��;1-ɾ��
}Money;


typedef struct Moneylofo
{
	char aCardname[50];           //����
	float tMoney;                 //��ֵ�˷ѽ��
	float fBalance;               //���
}Moneylofo;


#endif