#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "model.h"
#include "menu.h"

// 输出菜单
int main(void)
{
	int nSelection = 0; // 控制选择的变量
	printf("欢迎进入计费管理系统\n\n");
	do
	{ // 循环输出菜单
		outputMenu();
		while (scanf("%d", &nSelection) != 1)
		{
			printf("输入的菜单项序号错误!\n");
			while (getchar() != '\n')
				;
		}
		getchar();
		switch (nSelection)
		{ // 据输入的序号输出菜单
		case 1:
			add(); // 添加卡
			break;
		case 2:
			query(); // 查询卡
			break;
		case 3:
			logon(); // 上机
			break;
		case 4:
			settle(); // 下机
			break;
		case 5:
			addMoney(); // 充值
			break;
		case 6:
			refundMoney(); // 退费
			break;
		case 7:
			count(); // 查询统计
			break;
		case 8:
			annul(); // 注销卡
			break;
		case 0:
			exitApp(); // 退出
			break;
		default:
			printf("输入的菜单序号错误！\n\n");
			break;
		}
	} while (nSelection != 0); // 选择为0时循环停止

	return 0;
}