#include <windows.h>
#include "Main.h"
#include "EquipMgr\EquipMgr.h"
#include "EquipMgr\Equipment.h"
#include "UserInterface/UserInterface.h"

Equip* equip[5];

void System_Initialize()
{
	//初始化
}

void System_Destory();

int main()
{
	SetConsoleOutputCP(65001);
	System_Initialize();
	char ctrl;
	while (true)
	{
		SetupUI();
		printf("> 请输入欲执行的操作： ");
		ctrl = getchar();
		if (SystemControl(ctrl))
			break;
	}
	System_Destory();
	return 0;
}

void System_Destory()
{
	//析构
}