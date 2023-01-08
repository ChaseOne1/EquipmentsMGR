#include <windows.h>
#include "Main.h"
#include "EquipMgr\EquipMgr.h"
#include "EquipMgr\Equipment.h"
#include "UserInterface/UserInterface.h"

LinkList equipList;
Equip e1, e2, e3, e4, e5;
Node* a1, * a2, * a3, * a4, * a5;

void System_Initialize()
{
	a1 = MakeNode(&e1);
	a2 = MakeNode(&e2);
	a3 = MakeNode(&e3);
	a4 = MakeNode(&e4);
	a5 = MakeNode(&e5);
	a1->next = a2;
	a2->next = a3;
	a3->next = a4;
	a4->next = a5;
	e1.type = CHM;	e1.flag = true;
	e1.name = "machao";
	e1.buy_date = 20220807;
	e1.id = "D4B001";
	e1.price = 132.5;
	e1.scrap_date = 20190611;
	e2.type = ELC;	e2.flag = true;
	e2.name = "zhangsan";
	e2.buy_date = 20221212;
	e2.id = "D4B003";
	e2.price = 21.0;
	e2.scrap_date = 20190427;
	e3.type = MDC;	e3.flag = true;
	e3.name = "liangshuo";
	e3.buy_date = 20220112;
	e3.id = "D4B004";
	e3.price = 531.8;
	e3.scrap_date = 20192121;
	e4.type = CHM;	e4.flag = false;
	e4.name = "liuweihao";
	e4.buy_date = 20220911;
	e4.id = "D4B005";
	e4.price = 987.0;
	e4.scrap_date = 20190228;
	e5.type = CHM;	e5.flag = false;
	e5.name = "chenjintao";
	e5.buy_date = 20221211;
	e5.id = "D4B006";
	e5.price = 666.0;
	e5.scrap_date = 20191111;
	equipList.head = a1;
	equipList.tail = a5;
	equipList.LinkNum = 5;
}

void System_Destory();

int main()
{
	SetConsoleOutputCP(65001);//修改控制台的编码格式为utf-8
	System_Initialize();
	while (true)
	{
		SetupUI();
		printf("> 请输入欲执行的操作： ");
		if (SystemControl(getchar()))
			break;
	}
	System_Destory();
	return 0;
}

void System_Destory()
{
	Node* curr = equipList.head, * next;
	while (curr)
	{
		next = curr->next;
		free(curr->pEquip->name);
		free(curr->pEquip->id);
		free(curr->pEquip);
		free(curr);
		curr = next;
	}
}