#pragma once
#ifndef BILLING_FILE_H
#define BILLING_FILE_H

int getBillingCount();
Billing* readBilling();
int saveBilling(Billing* pb);                    //将计费信息保存到文件内
int updateBilling(Billing* p, int index);         //更新文件内的计费信息


#endif