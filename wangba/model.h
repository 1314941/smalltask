#pragma once
#ifndef MODEL_H
#define MODEL_H

#include<time.h>
//定义卡信息结构体
typedef struct Card  //卡信息结构体
{
	char aName[50];  //卡号
	char aPwd[50];       //密码
	int nStatus;     //卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
	time_t tStart;   //开卡时间
	time_t tEnd;     //卡的截止时间
	float fTotalUse;   //累计金额
	time_t tLast;       //最后使用时间
	int   nUseCount;   //使用次数
	float fBalance;    //余额
	int nDel;         //删除标志 0-未删除， 1-删除
}Card;

typedef struct CardNode             //卡信息节点
{
	Card data;
	struct CardNode* next;
}*lpCardNode, CardNode;



typedef struct Billing          //计费信息
{
	char aCardName[50];
	time_t tStart;                //上机时间
	time_t tEnd;               //下机时间
	float fAmount;              //花费金额
	int nstatus;                 //上机卡的状态
	int nDel;                       //删除标志
}Billing;


typedef struct BilllingNode             //计费信息节点
{
	Billing data;
	struct BillingNode* next;
}BillingNode, * lpBillingNode;



typedef struct Logonlofo                 //上机信息
{
	char aCardName[50];
	time_t tLogon;
	float fBalance;
}Logonlofo;


typedef struct Settlelofo               //下机信息
{
	char aCardName[50];
	time_t tStart;
	time_t tEnd;
	float fAmount;
	float fBalance;
}Settlelofo;



typedef struct Money               //充退费信息
{
	char aCardName[50];            //卡号
	time_t tTime;                  //充值退费的时间
	int nStatus;                   //状态：0表示充值；1表示退费
	float tMoney;                //充值退费金额
	int Del;                      //删除标志：0-未删除;1-删除
}Money;


typedef struct Moneylofo
{
	char aCardname[50];           //卡号
	float tMoney;                 //充值退费金额
	float fBalance;               //余额
}Moneylofo;


#endif