#pragma once
#ifndef BILLING_FILE_H
#define BILLING_FILE_H

int getBillingCount();
Billing* readBilling();
int saveBilling(Billing* pb);                    //���Ʒ���Ϣ���浽�ļ���
int updateBilling(Billing* p, int index);         //�����ļ��ڵļƷ���Ϣ


#endif