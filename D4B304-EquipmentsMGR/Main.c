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
	e2.type = ELC;	e2.flag = true;
	e3.type = MDC;	e3.flag = true;
	e4.type = CHM;	e4.flag = false;
	e5.type = CHM;	e5.flag = false;
	equipList.head = a1;
	equipList.tail = a5;
	equipList.LinkNum = 5;
}

void System_Destory();

int main()
{
	SetConsoleOutputCP(65001);
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
		free(curr);
		curr = next;
	}
}