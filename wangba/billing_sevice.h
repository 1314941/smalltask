#pragma once
#ifndef BILLING_FILE_H
#define BILLING_FILE_H

void releaseBillingList();                                      //�ͷżƷ���Ϣ����
void initBillinglist();                                      //��ʼ���Ʒ���Ϣ����
int getBilling();                                      //���ļ��ڶ�ȡ�Ʒ���Ϣ������
int addBilling(const char* fcardname);                  //��ӼƷ���Ϣ���ļ�
int queryBilling(const char* name,Billing* pb, int* pIndex);            //�ڼƷ���Ϣ�����ڲ�ѯ�Ʒ���Ϣ
void showinfomation(const char* name);              //����Ʒ���Ϣ

#endif