#include "..\Main.h"
#include "UserInterface.h"
#include "..\EquipMgr\EquipMgr.h"

extern const char* cEquipType[TOTAL + 1];
extern LinkList equipList;

void SetupUI()
{
	system("cls");
	MainMenuDisplay();
}

void MainMenuDisplay()
{
	printf("--------------设备管理系统------------------\n");
	printf("|					   |\n");
	printf("|	  1.添加设备：添加设备信息	   |\n");
	printf("|	  2.统计设备：分类统计设备	   |\n");
	printf("|	  3.设备报废：对设备报费处理       |\n");
	printf("|	  4.设备查询：按条件查询设备       |\n");
	printf("|	  5.设备排序：按条件排序设备       |\n");
	printf("|	  6.浏览设备：浏览全部设备         |\n");
	printf("|	  0.退出系统：退出	           |\n");
	printf("|					   |\n");
	printf("--------------------------------------------\n");
}

bool SystemControl(char ctrl)
{
	system("cls");	
	if (ctrl != '\n')	getchar();
	switch (ctrl)
	{
	case '1':
		break;
	case '2':
		Count();
		break;
	case '3':
		break;
	case '4':
		break;
	case '5':
		break;
	case '6':
		break;
	case '0':
		printf("确认退出？(Y/N)\n> ");
		char ch = getchar();	getchar();
		if (ch == 'Y' || ch == 'y')
			return true;
		else
			break;
	default:
		break;
	}
	return false;
}

void Count()
{
	system("cls");
	char type[6];	eEquipType TYPE = -1;
	const char* cEquipType[TOTAL + 1] = { "MEC","CHM","MDC","ELC","SPC","TOTAL" };
	unsigned char* result = TypeCount(&equipList);
	printf("请输入欲统计的类别： (机械类:MEC、化学类:CHM、医学类:MDC、电子类:ELC、特殊类:SPC、所有:TOTAL)\n退出请输入N\n");
	while (true)
	{
		printf("> ");
		gets(type);
		for (int i = 0; i < TOTAL + 1; ++i)
		{
			if (!strcmp(type, cEquipType[i]))
			{
				TYPE = i;
				break;
			}
		}
		if (type[0] == 'N' || type[0] == 'n')
			break;
		if (TYPE != -1)
			printf("%s 设备共有 %d 台（报废 %d 台）\n",
				cEquipType[TYPE], result[TYPE], result[TYPE + TOTAL + 1]);
		else
			printf("请重新输入\n");
	}
	for (int i = 0; i < TOTAL * 2; ++i)	free(result);
	result = NULL;
}