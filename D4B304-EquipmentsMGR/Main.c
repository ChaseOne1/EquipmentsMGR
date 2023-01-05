#include <windows.h>
#include "Main.h"
#include "EquipMgr\EquipMgr.h"
#include "EquipMgr\Equipment.h"
#include "UserInterface/UserInterface.h"
#include "EquipMgr\FileMgr.h"

LinkList equipList;

void System_Initialize(const char* srcFile)
{
	long long line = 1;
	equipList.LinkNum = 0;
	Equip* equip = ReadInfo(srcFile, line);
	equipList.head = MakeNode(equip);
	equipList.LinkNum++;
	if(strcmp("Equipments_Info.txt",srcFile))
		AddInfo("Equipments_Info.txt","a+", equip);
	line++;
	while (equip = ReadInfo(srcFile, line))
	{	
		if(!strcmp("Equipments_Info.txt",srcFile))
			AddEquip(&equipList, equip,0);
		else
			AddEquip(&equipList, equip,1);
		line++;
	}
}

void System_Destory();

int main(int atgc, char* argv[])
{
	SetConsoleOutputCP(65001);//修改控制台的编码格式为utf-8
	System_Initialize(atgc > 1 ? argv[1] : "Equipments_Info.txt");
	while (true)
	{
		SetupUI();
		printf("> 请输入欲执行的操作： ");
		if (SystemControl(getchar()))
			break;
	}
	system("pause");
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